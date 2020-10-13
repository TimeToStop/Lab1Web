document.getElementById('reset').addEventListener('click', function() {
    document.getElementById('error').innerHTML = '';
});

function validate() {
    let error         = document.getElementById('error')
    error.innerHTML   = '';

    let inputXElement = document.getElementById('inputX');
    let inputYElement = document.getElementById('inputY');
    let inputRElement = document.getElementById('inputR');

    let str_y = inputYElement.value.replace(',', '.');
    let str_r = inputRElement.value.replace(',', '.');

    let y = Number(str_y);
    let r = Number(str_r);

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
        let str = str_y;
        if(str.length > 5)
        {
            str = str.slice(0, 5);
            str = ''.concat(str, '1');
        }

        y = Number(str);

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
        let str = str_r;
        if(str.length > 5)
        {
            if(str[0] === '2' && str[1] === '.')
            {
                let is_all_zero = true;

                for(let i = 2; i < str.length; i++)
                {
                    if(str[i] !== '0')
                    {
                        is_all_zero = false;
                        break;
                    }
                }

                if(is_all_zero)
                {
                    error.innerText='Введенное значение R не входит в диапозон (2; 5)';
                    return false;
                }
            }
        
            
            str = str.slice(0, 5);
            str = ''.concat(str, '1');
        }
    
        r = Number(str);

        if(!(2 < r && r < 5))
        {
            error.innerText='Введенное значение R не входит в диапозон (2; 5)';
            return false;
        }
    }

    return true;
}