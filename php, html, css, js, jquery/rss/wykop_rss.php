<?php

    $xml = simplexml_load_file("http://www.wykop.pl/rss/");
    @ $file = fopen("wykop_rss_status", "r");
    if($file) {
        $file_line = fgets($file);
        fclose($file);
    }

    $file = fopen("wykop_rss_status", "w");
    $position = $xml->channel->item;

    $send_status = 0;

    again:
    for($i = $position->count() - 1; 0 <= $i; $i--) {
        if($send_status == 1) {
            $mail_adress = "adik.inf@gmail.com";
            $mail_title = $position[$i]->title;

            $mail_content = <<<EOF
                <html>
                    <head>
                        <title>{$position[$i]->title}</title>
                        <base href="{$position[$i]->link}">
                    </head>
                    <body id="msgFeedSummaryBody" selected="false">
                        {$position[$i]->description}
                    </body>
                </html>;
EOF;

            $header  = "X-Mozilla-Status: 0041\r\n";
            $header .= "X-Mozilla-Status2: 00000000\r\n";
            $header .= "X-Mozilla-Keys:\r\n";
            $header .= "From: rss-wykop@serwer".PHP_EOL;
            $header .= "MIME-Version: 1.0".PHP_EOL;
            $header .= "Content-Transfer-Encoding: 8bit".PHP_EOL;
            $header .= "Content-Base: ".$position[$i]->link.PHP_EOL;;
            $header .= "Content-Type: text/html; charset=utf-8";

            imap_mail($mail_adress, $mail_title, $mail_content, $header);
        }
        if($file_line == $position[$i]->title)
            $send_status = 1;
    }

    if($file_line == "") {
        $file_line = $position[$position->count() - 1]->title;
        goto again;
    }

    fputs($file, $position[0]->title);

    fclose($file);
?>
