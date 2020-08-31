function validate() {
    let error         = document.getElementById('error')
    error.innerHTML="";

    let inputXElement = document.getElementById('inputX');
    let inputYElement = document.getElementById('inputY');
    let inputRElement = document.getElementById('inputR');
    let y = Number(inputYElement.value);
    let r = Number(inputRElement.value);

    if(inputXElement.selectedIndex === 0)
    {
        error.innerText="Введите X";
        return false;
    }

    if(inputYElement.value === "")
    {
        error.innerText="Введите Y";
        return false;
    }

    if(y === NaN)
    {
        error.innerText="Введенное значение Y не число";
        return false;
    }
    else
    {
        if(!(-5 < y && y < 3))
        {
            error.innerText="Введенное значение Y не входит в диапозон (-5; 3)";
            return false;
        }
    }

    if(inputRElement.value === "")
    {
        error.innerText="Введите R";
        return false;
    }

    if(r === NaN)
    {
        error.innerText="Введенное значение R не число";
        return false;
    }
    else
    {
        if(!(2 < r && r < 5))
        {
            error.innerText="Введенное значение R не входит в диапозон (2; 5)";
            return false;
        }
    }

    return true;
}