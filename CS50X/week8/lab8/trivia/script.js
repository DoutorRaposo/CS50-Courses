window.addEventListener('DOMContentLoaded', () => {
    /*let old_html = document.querySelector('#mc').innerHTML;
    document.querySelector('#mc').innerHTML = old_html;*/
    document.querySelector(".correct").onclick = function() {
        document.querySelector('#mc_result').innerHTML = "Correct!";
        document.querySelector('.correct').style.backgroundColor = "green";
    }

    inputs = document.querySelectorAll(".incorrect");
    for (i = 0; i < inputs.length; i++) {
        inputs[i].addEventListener('click', function() {
            document.querySelector('#mc_result').innerHTML = "Incorrect!";
            this.style.backgroundColor = "red";
        });
    }

    document.querySelector('#check').onclick = function() {
        let input = document.querySelector('#fresponse').value;
        if (!input.toLowerCase().localeCompare("leaving las vegas")) {
            document.querySelector('#fr_result').innerHTML = "Correct!";
            document.querySelector('.answer').style.backgroundColor = "green"
        } else {
            document.querySelector('#fr_result').innerHTML = "Incorrect!";
            document.querySelector('.answer').style.backgroundColor = "red"
        }
    }
});