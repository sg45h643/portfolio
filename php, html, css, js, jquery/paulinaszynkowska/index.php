<!DOCTYPE HTML>
<head>
    <meta charset="utf-8" />
	<title>Paulina Szynkowska</title>
    <link rel="stylesheet" type="text/css" href="css/style.css" />
    <script src="script/jquery.js" type="text/javascript"></script>
    <script src="script/submenu.js" type="text/javascript"></script>
</head>
<body>

<div id="header"></div>
<div id="menu">
    <ul>
        <li style="width: 178px;"><a href="index.php">strona główna</a></li>
        <li class="menu-back"></li>
        <li style="width: 176px;"><a href="index.php?site=doswiadczenie">doświadczenie</a></li>
        <li class="menu-back"></li>
        <li id="psychotherapy" style="width: 173px;">psychoterapia</li>
        <li class="menu-back"></li>
        <li style="width: 129px;"><a href="index.php?site=warsztaty">warsztaty</a></li>
        <li class="menu-back"></li>
        <li style="width: 123px;"><a href="index.php?site=inspiracje">inspiracje</a></li>
        <li class="menu-back"></li>
        <li style="width: 107px;"><a href="index.php?site=kontakt">kontakt</a></li>
    </ul>
    <div id="submenu">
        <ul>
            <li><a href="index.php?site=warto_wiedziec">warto wiedzieć</a></li>
            <li><a href="index.php?site=rodzaje_i_cena">rodzaje i cena</a></li>
            <li><a href="index.php?site=o_psychoterapii_integracyjnej">o psychoterapii integracyjnej</a></li>
        </ul>
    </div>
</div>
<div id="line"></div>
<div id="main">
    <div id="left-box">
        <div class="box-border"></div>
        <div id="box-back">
            <div id="box-text">
            
            <?  
            if( $_GET['site'] == "")
                $_GET['site'] = "main.php";
                
                if (file_exists($_GET['site'] . ".php"))
                    require($_GET['site'] . ".php");
                else
                    require("main.php");
            ?>
            
            </div>
        </div>
        <div class="box-border"></div>
    </div>
    <div id="workshops">
        <div id="workshops-up"></div>
        <div id="workshops-back">
            <div id="workshops-next">najbliższe warsztaty:</div>
            <ul id="workshops-liks">
            
            <?
                require("lista_artykulow.php");
            ?>
            
            </ul>
        </div>
        <div id="workshops-down"></div>
    </div>
</div>
<div id="footer"></div>

</body>
</html>