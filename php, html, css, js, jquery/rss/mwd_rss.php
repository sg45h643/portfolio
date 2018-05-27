<?php
	$xml = simplexml_load_file("http://www.modlitwawdrodze.pl/podcast.xml");
	@ $file = fopen("mwd_rss_status", "r");
	$current_date = date("j M Y");

	@ $file_line = fgets($file);
	@ fclose($file);

	if(strstr($file_line, $current_date) !== False)
		exit;	

	$file = fopen("mwd_rss_status", "w");

	foreach($xml->channel->item as $i)
		if(strstr($i->pubDate, $current_date) !== False) {
			
			$mail_adress = "rozwoj7duchowy@gmail.com";
			$mail_title = "[MWD] ".date("j n Y");
			$mail_content = $i->description."<br/>".$i->guid;
                        $header = "From: rss-mwd@serwer".PHP_EOL;
                        $header .= "Content-type: text/html; charset=utf-8";

			imap_mail($mail_adress, $mail_title, $mail_content, $header);			

			fputs($file, $current_date);			
			break;
		}

	fclose($file);
?>