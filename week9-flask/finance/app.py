import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, datetime, pytz

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    userid = session["user_id"]
    data = db.execute("SELECT * FROM portfolios WHERE userid = ?", userid)
    cash = db.execute("SELECT * FROM users WHERE id = ?", userid)[0]["cash"]

    for row in data:
        row["price"] = lookup(row["symbol"])["price"]
        row["total"] = float(row["shares"]) * row["price"]

    return render_template("index.html", data=data, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        # Ensure symbol field is not empty
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("missing symbol", 400)

        # Ensure shares field is not empty, digit and not negative
        shares = request.form.get("shares")
        if not shares:
            return apology("missing shares", 400)

        if not shares.isdigit() or int(shares) < 0:
            return apology("invalid shares", 400)

        # Ensure symbol is valid
        quoted = lookup(symbol)
        if quoted == None:
            return apology("invalid symbol", 400)

        # Ensure cash is enough
        userid = session["user_id"]
        cash = db.execute("SELECT * FROM users WHERE id = ?", userid)[0]["cash"]
        price = quoted["price"]
        total = float(shares) * price

        if cash < total:
            return apology("can't afford", 400)

        # Record transaction
        db.execute(
            "INSERT INTO transactions (userid, type, symbol, shares, price, datetime) VALUES (?, ?, ?, ?, ?, ?)",
            userid,
            "buy",
            symbol,
            shares,
            price,
            datetime.datetime.now(pytz.timezone("US/Eastern")),
        )

        # Update user's cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total, userid)

        # Update user's portfolio
        if (
            len(
                db.execute(
                    "SELECT * FROM portfolios WHERE userid = ? AND symbol = ?",
                    userid,
                    symbol,
                )
            )
            == 0
        ):
            db.execute(
                "INSERT INTO portfolios (userid, symbol, name, shares) VALUES (?, ?, ?, ?)",
                userid,
                symbol,
                quoted["name"],
                shares,
            )

        else:
            db.execute(
                "UPDATE portfolios SET shares = shares + ? WHERE userid = ? AND symbol = ?",
                shares,
                userid,
                symbol,
            )

        # Redirect user to home page and notify user on successful transaction
        flash("Bought successfully!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    data = db.execute("SELECT * FROM transactions WHERE userid = ?", session["user_id"])
    return render_template("history.html", data=data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        # Ensure symbol field is not empty
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("missing symbol", 400)

        # Ensure symbol is valid
        quoted = lookup(symbol)
        if quoted == None:
            return apology("invalid symbol", 400)
        else:
            # Display name, symbol and price
            return render_template("quoted.html", quoted=quoted)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure verify password is the same with password
        elif not password == request.form.get("confirmation"):
            return apology("must verify password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username does not exists
        if len(rows) != 0:
            return apology("username already exists", 400)

        # Insert username and generated hash into database
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            generate_password_hash(password),
        )

        # Auto log user in
        session["user_id"] = db.execute(
            "SELECT id FROM users WHERE username = ?", username
        )[0]["id"]

        # Redirect user to homepage
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    userid = session["user_id"]

    if request.method == "POST":
        # Ensure symbol field is not empty
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("missing symbol", 400)

        # Ensure shares field is not empty
        shares = request.form.get("shares")
        if not shares:
            return apology("missing shares", 400)

        # Ensure shares is positive
        shares = int(shares)
        if shares == 0:
            return apology("shares must be positive", 400)

        # Ensure shares is not more than owned
        usershares = db.execute(
            "SELECT * FROM portfolios WHERE userid = ? AND symbol = ?", userid, symbol
        )[0]["shares"]
        if shares > usershares:
            return apology("too many shares", 400)

        # Record transactions
        cash = db.execute("SELECT * FROM users WHERE id = ?", userid)[0]["cash"]
        price = lookup(symbol)["price"]

        db.execute(
            "INSERT INTO transactions (userid, type, symbol, shares, price, datetime) VALUES (?, ?, ?, ?, ?, ?)",
            userid,
            "sell",
            symbol,
            shares,
            price,
            datetime.datetime.now(pytz.timezone("US/Eastern")),
        )

        # Update user's cash
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?",
            cash + (float(shares) * price),
            userid,
        )

        # Update user's portfolio
        db.execute(
            "UPDATE portfolios SET shares = shares - ? WHERE userid = ? AND symbol = ?",
            shares,
            userid,
            symbol,
        )

        if (shares - usershares) == 0:
            db.execute(
                "DELETE FROM portfolios WHERE userid = ? AND symbol = ?", userid, symbol
            )

        # Redirect user to home page and notify user on successful transaction
        flash("Sold successfully!")
        return redirect("/")

    else:
        data = db.execute("SELECT * FROM portfolios WHERE userid = ?", userid)
        return render_template("sell.html", data=data)


@app.route("/security", methods=["GET", "POST"])
@login_required
def security():
    """Change password"""

    if request.method == "POST":
        # Ensure password was submitted
        password = request.form.get("password")
        if not password:
            return apology("missing password", 400)

        # Ensure new password was submitted
        password_new = request.form.get("password_new")
        if not password_new:
            return apology("missing new password", 400)

        # Ensure verify password was submitted and the same with new password
        confirmation = request.form.get("confirmation")
        if not confirmation or not password_new == confirmation:
            return apology("must verify new password", 400)

        # Ensure password is correct
        userid = session["user_id"]
        hash = db.execute("SELECT * FROM users WHERE id = ?", userid)[0]["hash"]
        if not check_password_hash(hash, password):
            return apology("incorrect password", 400)

        # Ensure new password is not the same as the old one
        if check_password_hash(hash, password_new):
            return apology("new password must be different than the old one", 400)

        # Update new password
        db.execute(
            "UPDATE users SET hash = ? WHERE id = ?",
            generate_password_hash(password_new),
            userid,
        )

        # Redirect user to home page and notify user on successful change
        flash("Password changed successfully!")
        return redirect("/")

    else:
        return render_template("security.html")
