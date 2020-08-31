
<?php session_start(); ?>
<?php
function isEmpty()
{
    return (!isset($_GET['X']) && !isset($_GET['Y']) && !isset($_GET['R']));
}

function isValid()
{
    if(isset($_GET['X']) && isset($_GET['Y']) && isset($_GET['R']))
    {
        $X = $_GET['X'];
        $Y = str_ireplace(',','.', $_GET['Y']);
        $R = str_ireplace(',','.', $_GET['R']);
        if (!is_numeric($X))
        {
            return '<p id="error">X не число!</p>';
        }
        elseif (!is_numeric($Y))
        {
            return '<p id="error">Y не числo!</p>';
        }
        elseif (!is_numeric($R))
        {
            return '<p id="error">R не число!</p>';
        }


        if(!(-5 < $Y && $Y < 3))
        {
            return '<p id="error">Y не входит в диапозон (-5; 3)!</p>';
        }

        if(!(2 < $R && $R < 5))
        {
            return '<p id="error">R не входит в диапозон (2; 5)!</p>';
        }
    }
    else
    {
        return '<p id="error">Не заданы все параметры: X,Y,R</p>';
    }
}
?>

<!DOCTYPE html>
<html lang="ru">
<head>
    <meta content="text/html" charset=UTF-8"/>
    <title>Lab1</title>
    <style type="text/css">
        body {
            background: #45688E;
            font-family: monospace;
            color: black;
        }

        table {
            width: 100%;
            margin-top: 2%;
            text-align: center;
            font-family: monospace;
            font-size: 14pt;
            background-color: #FFFFFF;
        }


        img[src] {
            vertical-align: top;
            margin: 10px 0 0 0;
        }

        .Form p {
            margin-bottom: 2px;
        }

        input {
            margin: 0 0 0 1px;
        }

        .word-break {
            word-break: break-all;
        }

        #answer td {
            border: 2px solid black;
        }

        .Header {
            font-family: monospace;
            color: #45688E;
        }

        .Header * {
            margin-top: 5px;
        }

        .Header h1 {
            font-size: 25pt;
            color: darkblue;
        }

        .Header h2 {
            font-size: 18pt;
        }

        .Header h3 {
            font-size: 14pt;
            color: #5E81A8;
        }

        .Header h4 {
            font-size: 14pt;
            color: cornflowerblue;
        }

        .bold {
            font-weight: bold;
        }

        #error {
            color: #FF0000;
        }

        .answer {
            background: #5E81A8;
            width: 60%;
            table-layout: auto;
            margin: 10px 0 10px 20%;
            border: 1px solid black;
        }

        .answer td {
            border: 1px solid black;
        }

    </style>

</head>
<body>
    <table id="mainTable">
        <tbody>
        <tr>
            <td>
                <div class="Header bold">
                    <h1>Лабораторная работа №1 по Веб-программированию</h1>
                    <h2>Вариант №2219</h2>
                    <h3>Выполнил: Ратушняк Евгений Алексеевич</h3>
                    <h4>Группа: P3211</h4>
                </div>
            </td>
        </tr>
        <tr>
            <td>
                <img src="./img/coord.png">
            </td>
        </tr>
        <tr>
            <td>
                <form method="GET" action="input.php" onsubmit="return validate();">
                    <table class="Form">
                        <tbody>
                            <tr>
                                <td>
                                    <label for="inputX">Значение X:</label>
                                    <select name="X" id="inputX">
                                        <option disabled selected>Введите X</option>
                                        <option value="-4">-4</option>
                                        <option value="-3">-3</option>
                                        <option value="-2">-2</option>
                                        <option value="-1">-1</option>
                                        <option value="0">0</option>
                                        <option value="1">1</option>
                                        <option value="2">2</option>
                                        <option value="3">3</option>
                                        <option value="4">4</option>
                                    </select>
                                </td>
                            </tr>
                            <tr class="Blue">
                                <td>
                                    <p>
                                        <label for="inputY">Значение Y ∈ (-5;3):</label>
                                        <input type="text" id="inputY" autocomplete="off" name="Y" value=""/>
                                    </p>
                                </td>
                            </tr>
                            <tr>
                                <td>
                                    <p>
                                        <label for="inputR">Значение R ∈ (2;5):</label>
                                        <input type="text" id="inputR" autocomplete="off" name="R" value=""/>
                                    </p>
                                </td>
                            </tr>
                            <tr>
                                <td>
                                    <p>
                                        <input type="submit" value="Отправить"/>
                                        <input type="reset" value="Очистить"/>
                                    </p>
                                </td>
                            </tr>
                            <tr>
                                <td>
                                    <p id="error">
                                    </p>

<?php
    $err = isValid();

    if(!isEmpty() && !is_null($err))
    {
        echo $err;
    }
?>
                                </td>
                            </tr>
                        </tbody>
                    </table>
                </form>
            </td>
        </tr>
        <tr>
        <td>
            <table class="answer">
                <tbody>
                    <tr>
                        <td>X</td>
                        <td>Y</td>
                        <td>R</td>
                        <td>Ответ</td>
                        <td>Время</td>
                        <td>Время работы скрипта (в мс)</td>
                    </tr>


                    <?php
                    //unset($_SESSION['history']);
                    $start = microtime(TRUE);
                    $history = (isset($_SESSION['history']) && is_array($_SESSION['history'])) ? $_SESSION['history'] : [];

                    if (!isEmpty() && is_null(isValid()))
                    {
                        $X = floatval($_GET['X']);
                        $Y = floatval(str_ireplace(',', '.', $_GET['Y']));
                        $R = floatval(str_ireplace(',', '.', $_GET['R']));
                        $IS_SUCCESS = FALSE;

                        if ($X >= 0 && $Y >= 0)
                        {
                            if ($Y <= ($R - $X) / 2)
                            {
                                $IS_SUCCESS = TRUE;
                            }
                        }
                        elseif ($X < 0 && $Y < 0)
                        {
                            if ($X >= -$R && $Y >= -($R/2))
                            {
                                $IS_SUCCESS = TRUE;
                            }
                        }
                        elseif ($X >= 0 && $Y < 0)
                        {
                            if ( $X **2 + $Y ** 2 <= ($R/2) **2)
                            {
                                $IS_SUCCESS = TRUE;
                            }
                        }


                        setlocale(LC_ALL, 'ru_RU.UTF-8');
                        $time = strftime('%d %b %Y %H:%M:%S', time());
                        $executeion_time = strval(round((microtime(TRUE) - $start) * 1e+3, 3));

                        array_unshift($history, [
                                'X'               => $X,
                                'Y'               => $Y,
                                'R'               => $R,
                                'answer'          => ($IS_SUCCESS ? 'Попадает в точку' : 'Не попадает в точку'),
                                'time'            => $time,
                                'executeion_time' => $executeion_time,
                        ]);


                        $_SESSION['history'] = $history;
                    }

                    foreach ($history as $result) {
                    ?>
                    <tr>
                        <td><?=  $result['X']               ?></td>
                        <td><?=  $result['Y']               ?></td>
                        <td><?=  $result['R']               ?></td>
                        <td><?=  $result['answer']          ?></td>
                        <td><?=  $result['time']            ?></td>
                        <td><?=  $result['executeion_time'] ?></td>
                    </tr>
                    <?php
                    }
                    ?>
                </tbody>
            </table>
        </td>
    </tr>
</tbody>
</table>

<script type="text/javascript">
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

</script>

</body>
</html>