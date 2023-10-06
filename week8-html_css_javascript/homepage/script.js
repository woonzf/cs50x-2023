function showcontent() {
    let content = document.getElementById('content');
    let button = document.getElementById('button');
    if (content.style.display == 'block') {
      content.style.display = 'none';
      button.style.color = 'white';
    } else {
      content.style.display = 'block';
      button.style.color = 'grey';
    }
}
