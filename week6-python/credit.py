# TODO
def main():
    card_no = "abcd"

    # Prompt for input
    while not card_no.isdigit():
        card_no = input("Number: ")

    card_no = int(card_no)

    # Calculate checksum
    remainder = card_no
    i = 1
    sum246 = 0
    sum135 = 0

    while remainder > 1:
        # Check remainder
        last_digit = int(remainder % 10)

        # Remove 1 integer
        remainder /= 10

        # i = 2, 4, 6, ...
        if i % 2 == 0:
            if last_digit >= 5:
                # Example: 5 * 2 = 10, 1 + 0 = 1
                last_digit = last_digit * 2 % 10 + 1
            else:
                last_digit *= 2

            sum246 += last_digit
        # i = 1, 3, 5, ...
        else:
            sum135 += last_digit

        i += 1

    checksum = sum246 + sum135

    # Convert back to string to determine length and first 2 digits
    card_no = str(card_no)

    # Print AMEX, MASTERCARD, VISA or INVALID
    print(f"{cardtype(checksum, card_no)}")


def cardtype(checksum, card_no):
    amex = ["34", "37"]
    mastercard = ["51", "52", "53", "54", "55"]
    visa = ["40", "41", "42"]

    length = len(card_no)
    card_no2 = card_no[:2]

    # Check if checksum ends with 0
    if checksum % 10 == 0:
        if length == 15 and card_no2 in amex:
            return "AMEX"
        elif length == 16 and card_no2 in mastercard:
            return "MASTERCARD"
        elif length == 13 or length == 16 and card_no2 in visa:
            return "VISA"

        return "INVALID"

    return "INVALID"


main()
