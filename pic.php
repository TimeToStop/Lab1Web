<?php
header('Content-Type: image/bmp');

$DIR = 'E:/site/bmp/';

if(isset($_GET['X']) && isset($_GET['Y']) && isset($_GET['R']))
{
    $target = targetFileName($_GET['X'], $_GET['Y'], $_GET['R']);

    if(file_exists($target) === false)
    {
        exec( $DIR . 'bmp.exe ' . $DIR . ' ' . parse('X') . parse('Y') . parse('R'));
    }

    readfile($target);
}

function parse($val)
{
    return str_ireplace(',', '.', $_GET[$val]) . ' ';
}

function targetFileName($X, $Y, $R)
{
    return  $GLOBALS['DIR'] . 'results/resX' . to2Digit($X) . 'Y' . to2Digit($Y) . 'R' . to2Digit($R) . '.bmp';
}

function to2Digit($val)
{
    $temp = str_ireplace(',', '.', (floor($val * 10) / 10));

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