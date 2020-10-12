<?php
header('Content-Type: image/bmp');

$DIR = 'E:\\site\\bmp\\';

if(isset($_GET['X']) && isset($_GET['Y']) && isset($_GET['R']))
{
    $target = targetFileName($_GET['X'], $_GET['Y'], $_GET['R']);

    if(file_exists($target) === false)
    {
        $file = fopen($target, 'w');
        while(!chmod($target, 0777));    
        fclose($file);

        exec( $DIR . 'bmp ' . $DIR . ' ' . parse('X') . parse('Y') . parse('R'));
    }

    while(!file_exists($target));
    readfile($target);
}

function parse($val)
{
    return str_ireplace(',', '.', to2Digit($_GET[$val])) . ' ';
}

function targetFileName($X, $Y, $R)
{
    return  $GLOBALS['DIR'] . 'results/resX' . to2Digit($X) . 'Y' . to2Digit($Y) . 'R' . to2Digit($R) . '.bmp';
}

function to2Digit($val)
{
    if(strlen($val) > 5)
    {
        $val = substr($val, 0, 5);
    }

    $temp = str_ireplace(',', '.', (floor(str_ireplace(',', '.',$val) * 10) / 10));

    if(strpos($temp, '.') !== false)
    {
        return $temp;
    }
    else
    {
        return $temp . '.0';
    }
}
?>