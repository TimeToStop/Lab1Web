document.getElementById('reset').addEventListener('click', function() {
    document.getElementById('error').innerHTML = '';
});

function validate() {
    let error         = document.getElementById('error')
    error.innerHTML   = '';

    let inputXElement = document.getElementById('inputX');
    let inputYElement = document.getElementById('inputY');
    let inputRElement = document.getElementById('inputR');
    let y = Number(inputYElement.value.replace(',', '.'));
    let r = Number(inputRElement.value.replace(',', '.'));

    if(inputXElement.selectedIndex === 0)
    {
        error.innerText='Введите X';
        return false;
    }

    if(inputYElement.value === '')
    {
        error.innerText='Введите Y';
        return false;
    }

    if(isNaN(y))
    {
        error.innerText='Введенное значение Y не число';
        return false;
    }
    else
    {
        if(!(-5 < y && y < 3))
        {
            error.innerText='Введенное значение Y не входит в диапозон (-5; 3)';
            return false;
        }
    }

    if(inputRElement.value === '')
    {
        error.innerText='Введите R';
        return false;
    }

    if(isNaN(r))
    {
        error.innerText='Введенное значение R не число';
        return false;
    }
    else
    {
        if(!(2 < r && r < 5))
        {
            error.innerText='Введенное значение R не входит в диапозон (2; 5)';
            return false;
        }
    }

    return true;
}