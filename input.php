<!DOCTYPE html>
<html>
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
                    <a href="#">User</a>
                </li>
                <li>
                    <a href="#">Group</a>
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
        <img class="image" src="img/coord.png"/>
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
                <input class="button" type="submit" value="Отправить"/>
                <input class="button" type="reset" value="Очистить"/>
            </div>
            <p id="error">
            </p>
        </form>
    </div>
</div>
<div class="table">
    <div class="content">
        <div class="result-container">
            <div class="result">
                <div>
                    <img src="https://se.ifmo.ru/~s284705/pic.php"/>
                </div>
                <div class="frame-data">
                    <h5 class="result-header">Попал в точку</h5>
                    <div class="result-data">
                        <p>X = 0</p>
                        <p>Y = 0</p>
                        <p>R = 0</p>
                        <p>Execution Time 0s</p>
                    </div>
                    <div class="date">
                        <span>25 Jan 2015</span>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
</body>
</html>