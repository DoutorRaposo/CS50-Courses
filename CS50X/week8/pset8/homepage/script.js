function checkAnswer(form) {
    var inputValue = form.inputbox.value;
    if (!inputValue.toLowerCase().localeCompare("the unbearable weight of massive talent")) {
        alert("You are right!");
    } else {
        alert("You are wrong. Please, try again!");
    }
}