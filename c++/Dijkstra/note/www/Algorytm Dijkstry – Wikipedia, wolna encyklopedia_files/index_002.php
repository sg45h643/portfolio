//Autor skryptu: [[User:Tufor]] (z poprawkami dokonanymi przez [[User:Tar Lócesilion]])
mw.messages.set( {
	'badanie-anonymous-user': 'Anonimowy użytkownik',
	'badanie-form-warning': 'Zaznacz odpowiedzi na oba pytania.',
	'badanie-report-page': 'Wikiprojekt:Badania i rozwój Wikipedii/Badania/Pomoc/2015-03',
	'badanie-thankyou-text': 'Serdecznie dziekujemy za wzięcie udziału w naszym badaniu stron pomocy.<br />'+
		'Twoje odpowiedzi zostały zapisane na stronie: <a href="' +
		mw.util.getUrl('Wikiprojekt:Badania i rozwój Wikipedii/Badania/Pomoc/2015-03') + '">Wikiprojekt:Badania i rozwój Wikipedii/Badania/Pomoc/2015-03</a>.<br /><br />Miłego edytowania! ;-)',
	'badanie-tab-start': '{{Wikipedysta:Tufor/UXtabStart}}',
	'badanie-tab-end': '{{Wikipedysta:Tufor/UXtabKoniec}}',
	'badanie-disabled-button-text': 'Wysyłanie',
	'badanie-edit-summary': 'Wysłano ocenę strony pomocy',
	'badanie-question1': 'Czy pomogły Ci treści zawarte na tej stronie?',
	'badanie-question1-answer1':'Teraz wszystko wiem',
	'badanie-question1-answer2':'Tak, ale czegoś brakuje',
	'badanie-question1-answer3':'Mniej więcej',
	'badanie-question1-answer4':'W niewielkim stopniu',
	'badanie-question1-answer5':'Nadal nic nie wiem',
	'badanie-question2': 'Jak tutaj trafiłeś/aś?',
	'badanie-question2-default': 'Wybierz jedną z opcji',
	'badanie-question2-answer1': 'Przez inną stronę w Wikipedii',
	'badanie-question2-answer2': 'Odesłał(a) mnie tu wikipedyst(k)a',
	'badanie-question2-answer3': 'Przez wewnętrzną wyszukiwarkę Wikipedii',
	'badanie-question2-answer4': 'Przez zewnętrzną stronę/wyszukiwarkę',
	'badanie-question2-answer5': 'Inaczej (napisz poniżej jak)',
	'badanie-additional-comment-label': 'Dodatkowy komentarz',
	'badanie-additional-comment-placeholder': 'Napisz, co lubisz lub czego nie lubisz w tej stronie pomocy, a postaramy się ją poprawić.',
	'badanie-submit-button-text': 'Wyślij',
	'badanie-warn-anonymous': ' zgadzasz się na zapisanie Twojego adresu IP i ',
	'badanie-send-error': 'Wystąpił błąd podczas wysyłania formularza; serdecznie przepraszamy!',
	'badanie-copyright-warning': 'Klikając \„Wyślij\”,$1 wyrażasz nieodwołalną zgodę na udostępnianie Twojego komentarza na licencjach <a href="//creativecommons.org/licenses/by-sa/3.0/">CC-BY-SA 3.0</a> i <a href="//www.gnu.org/copyleft/fdl.html">GFDL</a> oraz na wykorzystanie go w dowolnej formie pod warunkiem podania przynajmniej hiperłącza lub adresu URL do <a href="'+mw.util.getUrl('Wikiprojekt:Badania i rozwój Wikipedii/Badania/Pomoc/2015-03') + '">strony, na której zostanie opublikowany</a>. Zobacz szczegółowe informacje o <a href="//wikimediafoundation.org/wiki/Warunki_korzystania">warunkach korzystania</a>.'
});

function UXsprawdzPoprawnosc(ocena, skad)
{
	if(ocena&&skad!='0')
	{
		if(document.getElementById("UXpoleBlad"))
			UXpoleBlad.parentNode.removeChild(UXpoleBlad);
		return true;
	}
	if(!document.getElementById("UXpoleBlad"))
	{
		var poleBlad = document.createElement('div');
		poleBlad.setAttribute("id", "UXpoleBlad");
		poleBlad.style.textAlign="center";
		poleBlad.style.clear="both";
		poleBlad.style.fontWeight="bold";
		
		var poleBladText=mw.msg('badanie-form-warning');
		poleBlad.innerHTML=poleBladText;
		
		document.getElementById("UXpudelko").appendChild(poleBlad);
	}
	return false;
}

function UXwyslijOdpowiedz()
{
	var form = document.forms.formularz;
	var komentarz = form.UXkomentarz.value;
	var ocena = form.UXocena.value;
	var skad = form.UXjaktrafiles.value;
	var czyPoprawny = UXsprawdzPoprawnosc(ocena, skad); //sprawdza czy formularz zostal wypelniony poprawnie
	
	if(czyPoprawny===true)
	{
		document.getElementById('UXzapisz').disabled=true;
		document.getElementById('UXzapisz').value=mw.msg('badanie-disabled-button-text');
		var strona = mw.config.get('wgTitle');
		var kto;
		
		if (!mw.config.get('wgUserName'))
			kto = mw.msg('badanie-anonymous-user');
		else
			kto = mw.config.get('wgUserName');
		
		var formulka = "{{Wikipedysta:Tufor/UXtabWiersz|data=~~" + "~~" + "~ |kto=" +kto+ " |kto2 = {{subs"+"t:REVISIONUSER}} |strona=" +
			strona+ " |ocena=" +ocena+ " |jak=" +skad+ " |komentarz=" +komentarz+ "}}\n";
		
		var api = JsMwApi( mw.util.wikiScript( 'api' ) );
		var pageHandler = api.page( mw.msg('badanie-report-page') );
		var newText;
		pageHandler.edit( function( text, save_function, res )//zaczynamy edycje strony
		{
			var toReplace = mw.msg('badanie-tab-end');
			if(text==="") //jesli jeszcze nie ma strony zbierajacej wyniki
				newText=mw.msg('badanie-tab-start') +'\n'+ formulka + toReplace;
			else
			{
				newText = text.replace(toReplace, formulka + toReplace);
				if(newText===text)
					newText=text+'\n\n'+formulka;
			}
			//save the new content
			save_function(
				newText,
				{
					summary: mw.msg('badanie-edit-summary'),
					minor: false
				}, 
				function( res )
				{
						var UXrodzic = document.getElementById("UXpudelko");
						UXrodzic.removeChild(document.getElementById("UXpud1"));
						UXrodzic.removeChild(document.getElementById("UXpud2"));
						UXrodzic.removeChild(document.getElementById("UXpud3"));
						UXrodzic.removeChild(document.getElementById("UXpudCopyright"));
							
					if ( res && res.edit && res.edit.result && res.edit.result === 'Success' )
					{
						//zapisano pomyślnie - usuwamy treść formularza i wstawiamy podziękowanie
						var UXpodziekowanie = document.createElement("div");
						UXpodziekowanie.style.textAlign="center";
						UXpodziekowanie.innerHTML = mw.msg('badanie-thankyou-text');
						UXrodzic.appendChild(UXpodziekowanie);
					}
					else {
						//błąd przy zapisywaniu
						var UXbladprzywysylaniu = document.createElement("div");
						UXbladprzywysylaniu.style.textAlign="center";
						UXbladprzywysylaniu.innerHTML = mw.msg('badanie-send-error');
						UXrodzic.appendChild(UXbladprzywysylaniu);
						}
					}
				);
		});
	}
}

function UXwygenerujFormularz()
{
	var gdzie = document.getElementById("catlinks"); //gdzie zaczepić formularz - nad kategoriami
	
	var UXformularz=document.createElement('form'); //tworzymy formularz
	UXformularz.setAttribute("id", "formularz");
	UXformularz.setAttribute("name", "formularz");
	UXformularz.className="mw-ui-vform";
	
	var UXpudelko=document.createElement('div'); //tworzymy zewnętrzne pudełko -div w którym są kolejne divy
	UXpudelko.setAttribute("id", "UXpudelko");
	UXpudelko.style.backgroundColor="#fff";
	UXpudelko.className="mw-ui-vform-field";
	UXpudelko.style.padding="10px";
	UXpudelko.style.border="1px solid #aaa";
	UXpudelko.style.borderRadius="0.2em";
	UXpudelko.style.margin="20px auto 0 auto";
	UXpudelko.style.maxWidth="715px";
	UXpudelko.style.clear="both";
	
	//pierwszy box: pierwsze pytanie
	var UXpodpudelko1=document.createElement('div');
	UXpodpudelko1.style.float="left";
	UXpodpudelko1.style.width="40%";
	UXpodpudelko1.setAttribute("id", "UXpud1");
	UXpodpudelko1.className="mw-ui-vform-field";
	
	var pyt1 = document.createElement('span');
	var pyt1_text=document.createTextNode(mw.msg('badanie-question1'));
	pyt1.appendChild(pyt1_text);
	pyt1.style.fontWeight="bold";
	UXpodpudelko1.appendChild(pyt1);
	
	var pyt1div = document.createElement('div');
	pyt1div.className = "mw-ui-vform-field mw-ui-radio";
	pyt1div.style.verticalAlign="middle";
	
	for(var i=1;i<=5;i++)
	{
		var pyt1input = document.createElement('input');
		pyt1input.setAttribute("type", "radio");
		pyt1input.setAttribute("name", "UXocena");
		pyt1input.setAttribute("value", (6-i));
		pyt1input.setAttribute("id", "UXpyt1odp"+(i));
		pyt1div.appendChild(pyt1input);
		
		var pyt1label = document.createElement('label');
		pyt1label.setAttribute("for", "UXpyt1odp"+(i));
		pyt1label.innerHTML = mw.msg('badanie-question1-answer'+i)+'<br />';
		pyt1div.appendChild(pyt1label);
	}
	UXpodpudelko1.appendChild(pyt1div);
	UXpudelko.appendChild(UXpodpudelko1);
	
	//drugi box: drugie pytanie + dodatkowy komentarz
	var UXpodpudelko2=document.createElement('div');
	UXpodpudelko2.style.float="left";
	UXpodpudelko2.style.width="45%";
	UXpodpudelko2.setAttribute("id", "UXpud2");
	UXpodpudelko2.className="mw-ui-vform-field";
	var pyt2div = document.createElement('div');
	pyt2div.className="mw-ui-vform-field";
	var pyt2 = document.createElement('span');
	var pyt2_text = document.createTextNode(mw.msg('badanie-question2'));
	pyt2.appendChild(pyt2_text);
	pyt2.style.fontWeight = "bold";
	pyt2div.appendChild(pyt2);
	
	var pyt2selectdiv = document.createElement('div');
	pyt2selectdiv.className="mw-ui-vform-field";
	
	var pyt2select = document.createElement('select');
	pyt2select.setAttribute("name", "UXjaktrafiles");
	
	var pyt2default = document.createElement('option');
	pyt2default.disabled=true;
	pyt2default.selected=true;
	pyt2default.setAttribute("value", "0");
	pyt2default.innerHTML=mw.msg('badanie-question2-default');
	pyt2select.appendChild(pyt2default);
	
	for(i=1;i<=5;i++)
	{
		var pyt2option = document.createElement('option');
		pyt2option.setAttribute("value", i);
		pyt2option.innerHTML=mw.msg('badanie-question2-answer'+i);
		pyt2select.appendChild(pyt2option);
	}
	pyt2selectdiv.appendChild(pyt2select);
	pyt2div.appendChild(pyt2selectdiv);
	UXpodpudelko2.appendChild(pyt2div);
	
	var commdiv=document.createElement('div');
	var commspan = document.createElement('span');
	commspan.style.fontWeight="bold";
	var commspan_text = document.createTextNode(mw.msg('badanie-additional-comment-label'));
	commspan.appendChild(commspan_text);
	commdiv.appendChild(commspan);
	
	var commarea = document.createElement('textarea');
	commarea.setAttribute("name", "UXkomentarz");
	commarea.className="mw-ui-input";
	commarea.setAttribute("cols", "50");
	commarea.setAttribute("rows", "4");
	commarea.placeholder= mw.msg('badanie-additional-comment-placeholder');
	commdiv.appendChild(commarea);
	
	UXpodpudelko2.appendChild(commdiv);
	UXpudelko.appendChild(UXpodpudelko2);
	
	//trzeci box: przycisk wyślij
	var UXpodpudelko3=document.createElement('div');
	UXpodpudelko3.style.float="left";
	UXpodpudelko3.style.width="15%";
	UXpodpudelko3.setAttribute("id", "UXpud3");
	var UXwyslij = document.createElement('input');
	UXwyslij.setAttribute("onclick","UXwyslijOdpowiedz()");
	UXwyslij.setAttribute("type", "button");
	UXwyslij.setAttribute("value", mw.msg('badanie-submit-button-text'));
	UXwyslij.setAttribute("id", "UXzapisz");
	UXwyslij.className = "mw-ui-button mw-ui-constructive";
	UXpodpudelko3.appendChild(UXwyslij);
	UXpudelko.appendChild(UXpodpudelko3);
	
	var UXcopyrightwarning=document.createElement('div');
	UXcopyrightwarning.style.fontSize="75%";
	UXcopyrightwarning.style.textAlign="center";
	UXcopyrightwarning.style.clear="both";
	UXcopyrightwarning.setAttribute("id", "UXpudCopyright");
	var UXcopyrighttext=mw.msg('badanie-copyright-warning');
	if(!mw.config.get('wgUserName'))
		UXcopyrighttext = UXcopyrighttext.replace('$1', mw.msg('badanie-warn-anonymous'));
	else
		UXcopyrighttext = UXcopyrighttext.replace('$1', '');
		
	UXcopyrightwarning.innerHTML = UXcopyrighttext;
	UXpudelko.appendChild(UXcopyrightwarning);
	
	UXformularz.appendChild(UXpudelko);
	gdzie.parentNode.insertBefore(UXformularz, gdzie);
}
function UXSprawdzCzyWyswietlic()
{
	if(mw.config.get('wgAction')!="view")
		return false;
	if(mw.config.get('wgCurRevisionId')!=mw.config.get('wgRevisionId'))
		return false;
	return true;
}

if(mw.config.get('wgNamespaceNumber')==12) //dziala tylko w przestrzeni Pomoc (przestrzen 12)
{
	if(UXSprawdzCzyWyswietlic()===true)
	{
		importScript('MediaWiki:Gadget-JsMwApi.js');
		mw.loader.load('mediawiki.ui.input');
		mw.loader.load('mediawiki.ui.forms');
		UXwygenerujFormularz();
	}
}