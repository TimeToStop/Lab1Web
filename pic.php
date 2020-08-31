<?php
$image = imagecreatefrompng('img/coord.png');
$size = getimagesize($image);

imageellipse($image, 0, 0, 10, 10);

header("Content-Type: image/png");
imagepng($image);
imagedestroy($image);
?>