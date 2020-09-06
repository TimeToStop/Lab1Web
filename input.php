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
        <meta charset="UTF-8"/>
        <title>Lab1</title>
        <link rel="stylesheet" type="text/css" href="css/style.css"/>
    </head>
    <body>
        <div class="header">
            <div class="content">
                <div>
                    <h2 class="head-label">WebProgramming</h2>
                    <ul class="menu">
                        <li>
                            <a href="https://github.com/TimeToStop">User</a>
                        </li>
                        <li>
                            <a href="https://isu.ifmo.ru/pls/apex/f?p=2143:GR:120853349933398::NO::GR_GR,GR_DATE,GR_TYPE:p3211,01.09.2020,group">Group</a>
                        </li>
                        <li>
                            <a href="https://www.google.com/">Other</a>
                        </li>
                    </ul>
                </div>
            </div>
        </div>
        <div class="maininfo">
            <div class="content">
                <h1 class="content-header">Лабораторная работа №1</h1>
                <h3 class="content-header">По веб-программированию</h3>
                <h3 class="content-header">Вариант №2219</h3>
                <h3 class="content-header">Выполнил: Ратушняк Евгений </h3>
                <h3 class="content-header">Группа: P3211</h3>
            </div>
        </div>
        <div class="coord">
            <div class="content">
                <img class="image" src="img/coord.png" alt="coordinate task"/>
            </div>
        </div>
        <div class="form">
            <div class="content">
                <form method="GET" action="input.php" onsubmit="return validate();">
                    <div class="form-container">
                        <div class="column">
                            <div class="cell">
                                <label for="inputX">Значение X:</label> <br/>
                                <select name="X" id="inputX" class="x-input">
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
                            </div>
                            <div class="cell">
                                <label for="inputY">Значение Y ∈ (-5;3):</label><br/>
                                <input class="text-edit" type="text" id="inputY" autocomplete="off" name="Y" value=""/>
                            </div>
                        </div>
                        <div class="column">
                            <div class="cell">
                                <label for="inputR">Значение R ∈ (2;5):</label> <br/>
                                <input class="text-edit" type="text" id="inputR" autocomplete="off" name="R" value=""/>
                            </div>
                        </div>
                    </div>
                    <div class="center-buttons">
                        <input type ="hidden" name="uniqid" value="<?= uniqid()?>"/>
                        <input class="button" type="submit" value="Отправить"/>
                        <input class="button" type="reset" value="Очистить" id="reset"/>
                    </div>
                    <p id="error">
                    </p>
                </form>
            </div>
        </div>
        <div class="table">
            <div class="content">
                <div class="result-holder">
            <?php
//            unset($_SESSION['history']);
            $start = microtime(TRUE);
            $history = (isset($_SESSION['history']) && is_array($_SESSION['history'])) ? $_SESSION['history'] : [];

            if (!isEmpty() && is_null(isValid()) && isset($_GET['uniqid']))
            {
                $uniqid = $_GET['uniqid'];
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
                $executeion_time = strval(round((microtime(TRUE) - $start) * 1e+6, 3));

                if(count($history) == 0 || $history[0]['uniqid'] !== $uniqid)
                {
                    array_unshift($history, [
                        'X'               => $X,
                        'Y'               => $Y,
                        'R'               => $R,
                        'answer'          => ($IS_SUCCESS ? 'Попадает в точку' : 'Не попадает в точку'),
                        'time'            => $time,
                        'executeion_time' => $executeion_time,
                        'uniqid'          =>  $uniqid
                    ]);

                }

                $_SESSION['history'] = $history;
            }


            foreach ($history as $result) {
                ?>

                <div class="result">
                    <div>
                        <img src="http://localhost:8888/pic.php?X=<?=$result['X']?>&Y=<?=$result['Y']?>&R=<?=$result['R']?>" alt="result"/>
                    </div>
                    <div>
                        <h5 class="result-header"><?= $result['answer'] ?></h5>
                        <div class="result-data">
                            <p>X = <?= $result['X']?></p>
                            <p>Y = <?= $result['Y']?></p>
                            <p>R = <?= $result['R']?></p>
                            <p>Execution: <?=$result['executeion_time'] ?> ms</p>
                        </div>
                        <div class="execution-date">
                            <?= $result['time'] ?>
                        </div>
                    </div>
                </div> 

                <?php
            }
            ?>
            </div>
        </div>
    </div>
<script src="js/main.js">
</script>
</body>
</html>