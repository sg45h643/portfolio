/*
USAGE:
On en.wikipedia, add the following line:

if ( mw.config.get( 'wgCanonicalSpecialPageName' ) === 'Search' ||  ( mw.config.get( 'wgArticleId' ) === 0 && mw.config.get( 'wgCanonicalSpecialPageName' ) === false ) ) {
	importScript('MediaWiki:Wdsearch.js');
}

to your [[Special:Mypage/common.js|common.js]] page. On other Wikipedias, add

if ( mw.config.get( 'wgCanonicalSpecialPageName' ) === 'Search' ||  ( mw.config.get( 'wgArticleId' ) === 0 && mw.config.get( 'wgCanonicalSpecialPageName' ) === false ) ) {
	importScriptURI("//en.wikipedia.org/w/index.php?title=MediaWiki:Wdsearch.js&action=raw&ctype=text/javascript");
}

instead. To change the header line to your language, have an admin add the appropriate line to this page.

You can set the variable "wdsearch_results" to change the maximum number of search results from the default 10.

*/
/*global jQuery, mediaWiki, wd_auto_desc, wdsearch_results, importScriptURI */
/*jshint strict:false, browser:true, quotmark:single */
(function( $, mw ) {

var i18n = {
	'en' : {
		'commons_cat' : 'Commons category' ,
		'wikipedias' : 'Wikipedia articles' ,
		'wikivoyages' : 'Wikivoyage travel guides' ,
		'wikisources' : 'Wikisource pages' ,
		'header' : 'Wikidata search results' ,
		'reasonator' : 'Show item details on Reasonator'
	},
	'bn' : {
		'commons_cat' : 'কমন্স বিষয়শ্রেণী' ,
		'wikipedias' : 'উইকিপিডিয়া নিবন্ধ' ,
		'header' : 'উইকিউপাত্ত অনুসন্ধানের ফলাফল',
		'reasonator' : 'Reasonator-এ আইটেমের বিস্তারিত দেখাও'
	},
	'cs' : {
		'commons_cat' : 'Kategorie na Wikimedia Commons' ,
		'wikipedias' : 'Články na Wikipedii' ,
		'header' : 'Výsledky vyhledávání na Wikidatech' ,
		'reasonator' : 'Zobrazit podrobnosti nástrojem Reasonator'
	},
	'de' : {
		'commons_cat' : 'Kategorie auf Commons' ,
		'wikipedias' : 'Wikipedia-Artikel' ,
		'wikivoyages' : 'Wikivoyage-Reiseführer' ,
		'wikisources' : 'Wikisource-Artikel' ,
		'header' : 'Wikidata-Suchergebnisse' ,
		'reasonator' : 'Zeige die Eigenschaften auf Reasonator'
	},
	'el' : {
		'commons_cat' : 'Κατηγορία στα Commons' ,
		'wikipedias' : 'Λήμματα στη Βικιπαίδεια' ,
		'header' : 'Αποτελέσματα αναζήτησης στα Wikidata'
	},
	'eo' : {
		'commons_cat' : 'Komuneja kategorio' ,
		'wikipedias' : 'Vikipediaj artikoloj' ,
		'header' : 'Serĉorezultoj de Vikidatumoj' ,
		'reasonator' : 'Montri detalojn en Reasonator'
	},
	'es' : {
		'commons_cat' : 'Categoría en Commons' ,
		'wikipedias' : 'Artículos en Wikipedia' ,
		'header' : 'Resultados de la búsqueda en Wikidata' ,
		'reasonator' : 'Mostrar los detalles en Reasonator'
	},
	'eu' : {
		'commons_cat' : 'Commonseko kategoria' ,
		'wikipedias' : 'Wikipediako artikuluak' ,
		'header' : 'Wikidatako bilaketaren emaitzak' ,
		'reasonator' : 'Erakutsi Reasonatorreko xehetasunak'
	},
	'fa' : {
		'commons_cat' : 'رده انبار' ,
		'wikipedias' : 'مقاله ویکی‌پدیا' ,
		'wikivoyages' : 'راهنما در ویکی‌سفر' ,
		'wikisources' : 'صفحه در ویکی‌نبشته' ,
		'header' : 'نتیجه جستجو در ویکی‌داده' ,
		'reasonator' : 'اطلاعات بیشتر در مورد این آیتم در ریزنیتور'
	},
	'fr' : {
		'commons_cat' : 'Catégorie sur Commons' ,
		'wikipedias' : 'Articles sur Wikipédia' ,
		'header' : 'Résultats sur Wikidata'
	},
	'gu' : {
		'commons_cat' : 'કોમન્સ કેટેગરી' ,
		'wikipedias' : 'વિકિપીડિયાના લેખો' ,
		'header' : 'વિકિડેટા શોધ પરિણામો' ,
		'reasonator' : 'રિઝોનેટર પર આઇટમની વિગતો બતાવો'
	},
	'he' : {
		'commons_cat': 'קטגוריית ויקישיתוף',
		'wikipedias': 'ערכים בוויקיפדיה',
		'header': 'תוצאות חיפוש בוויקינתונים'
	},
	'hu' : {
		'commons_cat' : 'Commons-kategória' ,
		'wikipedias' : 'Wikipédia-szócikkek' ,
		'wikisources' : 'Wikiforrás-lapok' ,
		'header' : 'Wikidata keresési eredmények'
	},
	'id' : {
		'commons_cat' : 'Kategori Commons' ,
		'wikipedias' : 'Artikel Wikipedia' ,
		'header' : 'Hasil pencarian Wikidata' ,
		'reasonator' : 'Tunjukkan detil item di Reasonator'
	},
	'ilo' : {
		'commons_cat' : 'Kategoria ti Commons' ,
		'wikipedias' : 'Dagiti artikulo ti Wikipedia' ,
		'header' : 'Dagiti resulta ti panagbiruk iti Wikidata' ,
		'reasonator' : 'Ipakita dagiti salaysay ti banag iti Reasonator'
	},
	'it' : {
		'commons_cat' : 'Categoria in Commons' ,
		'wikipedias' : 'Voci di Wikipedia' ,
		'header' : 'Risultati da Wikidata'
	},
	'ja' : {
		'commons_cat' : 'コモンズのカテゴリ' ,
		'wikipedias' : 'ウィキペディアの記事' ,
		'wikivoyages' : 'Wikivoyage の旅行ガイド' ,
		'wikisources' : 'ウィキソースのページ' ,
		'header' : 'ウィキデータの検索結果' ,
		'reasonator' : 'Reasonator で項目の詳細を見る'
	},
	'kk' : {
		'commons_cat' : 'Ортаққордағы санаты' ,
		'wikipedias' : 'Уикипедиядағы мақаласы' ,
		'header' : 'Уикидеректегі іздеу нәтижелері' ,
		'reasonator' : 'Reasonator арқылы толығырақ қарау'
	},
	'nb' : {
		'commons_cat' : 'Commons-kategori' ,
		'wikipedias' : 'Wikipedia-artikler' ,
		'wikivoyages' : 'Wikivoyage-sider' ,
		'wikisources' : 'Wikikilden-sider' ,
		'header' : 'Søkeresultater fra Wikidata' ,
		'reasonator' : 'Vis detaljer om elementet i Reasonator'
	},
	'nn' : {
		'commons_cat' : 'Commons-kategori' ,
		'wikipedias' : 'Wikipedia-artiklar' ,
		'wikivoyages' : 'Wikivoyage-sider' ,
		'wikisources' : 'Wikikilden-sider' ,
		'header' : 'Søkjeresultat frå Wikidata' ,
		'reasonator' : 'Syn detaljar om elementet i Reasonator'
	},
	'pl' : {
		'commons_cat' : 'Kategoria na Commons' ,
		'wikipedias' : 'Artykuły w Wikipedii',
		'header' : 'Wyniki wyszukiwania w Wikidata' ,
		'reasonator' : 'Pokaż szczegóły w Reasonatorze'
	},
	'pt' : {
		'commons_cat' : 'Categoria no Commons' ,
		'wikipedias' : 'Artigos da Wikipédia' ,
		'header' : 'Resultados da busca no Wikidata'
	},
	'pt-br' : {
		'commons_cat' : 'Categoria no Commons' ,
		'wikipedias' : 'Artigos da Wikipédia' ,
		'header' : 'Resultados da busca no Wikidata'
	},
	'nl' : {
       'commons_cat' : 'Commons-categorie' ,
       'wikipedias' : 'Wikipedia-artikelen' ,
       'wikivoyages' : 'Wikivoyage-reisgidsen' ,
       'wikisources' : 'Wikisource-pagina\'s' ,
       'header' : 'Wikidata-zoekresultaten' ,
       'reasonator' : 'Bekijk itemgegevens op Reasonator'
	},
	'ru' : {
		'commons_cat' : 'Категория Викисклада' ,
		'wikipedias' : 'Статьи Википедии' ,
		'header' : 'Результаты поиска в Викиданных' ,
		'reasonator' : 'Посмотреть подробности через Reasonator'
	},
	'sk' : {
		'commons_cat' : 'Kategória na Commons' ,
		'wikipedias' : 'Články na Wikipédii' ,
		'header' : 'Výsledky hľadania na Wikiúdajoch' ,
		'reasonator' : 'Zobraziť podrobnosti v Reasonatore'
	},
	'sv' : {
		'commons_cat' : 'Kategorier på Commons' ,
		'wikipedias' : 'Wikipediaartiklar' ,
		'header' : 'Sökresultat från Wikidata'
	},
	'udm' : {
		'commons_cat' :	'Викискладысь категория' ,
		'wikipedias' : 'Википедиысь статьяос' ,
		'header' : 'Викиданнойёсысь утчанлэн йылпумъянъёсыз' ,
		'reasonator' : 'Тыро-пыдогес учконо Reasonator пыр'
	},
	'ur' : {
		'commons_cat' : 'کومنز زمرہ' ,
		'wikipedias' : 'ویکیپیڈیا مضامین' ,
		'wikivoyages' : 'سفری رہنما برائے ویکی سفر' ,
		'wikisources' : 'ویکی ماخذ صفحات' ,
		'header' : 'ویکی ڈیٹا میں نتیجہ تلاش' ,
		'reasonator' : 'ریزونیٹر میں آئٹم کی تفصیلات دکھائیں'
	},
	'vi' : {
		'commons_cat' : 'Thể loại Commons' ,
		'wikipedias' : 'Bài viết Wikipedia' ,
		'wikivoyages' : 'Bài viết Wikivoyage' ,
		'header' : 'Kết quả tìm kiếm Wikidata' ,
		'reasonator' : 'Xem chi tiết khoản mục trên Reasonator'
	},
	'zh' : {
		'commons_cat' : '维基共享资源类别' ,
		'wikipedias' : '维基百科文章' ,
		'header' : '维基数据搜索结果' ,
		'reasonator' : '上Reasonator显示项目的详细信息'
	}
};

var mode = 'searchresults';
var i18n_lang = mw.config.get( 'wgUserLanguage' );
var api = '//www.wikidata.org/w/api.php?callback=?' ;

mw.log( 'Initiating WDsearch' ) ;
if ( undefined === i18n[i18n_lang] ) i18n_lang = 'en' ; // Fallback
if ( mw.config.get( 'wgCanonicalSpecialPageName' ) !== 'Search' && mw.config.get( 'wgArticleId' ) !== 0 ) return;

$(document).ready ( function () {
	var results = $('div.searchresults') ;
	if ( results.length === 0 ) {
		mode = 'noarticletext' ;
		results = $('div.noarticletext table') ;
	}
	if ( results.length === 0 ) return ; // No search results, no search page. Bye.

	mw.log( 'Preparing WDsearch' ) ;
	importScriptURI( '//en.wikipedia.org/w/index.php?title=MediaWiki:Wdsearch-autodesc.js&action=raw&ctype=text/javascript' );

	function run () {

		mw.log( 'Trying to run WDsearch' );

		if ( typeof wd_auto_desc === 'undefined' ) {
			// Wait until the above autodesc script has loaded
			setTimeout ( run , 100 ) ;
			return ;
		}

		mw.log( 'Running WDsearch' ) ;

		wd_auto_desc.lang = i18n_lang;

		var query ;
		if ( mode == 'searchresults' ) {
			query = $('#powerSearchText').val() ;
			if ( $('#powerSearchText').length === 0 ) query = $('#searchText').val() ;
		} else if ( mode == 'noarticletext' ) query = mw.config.get( 'wgPageName' );

		mw.log ( 'Using mode ' + mode + ' and query :' + query ) ;

		$.getJSON ( api , {
			action:'query',
			list:'search',
			srsearch:query,
			srlimit:(typeof wdsearch_results === 'undefined'?10:wdsearch_results),
			srnamespace:0,
			format:'json'
		} , function (d) {
			mw.log(d);
			if ( undefined === d.query || undefined === d.query.search || d.query.search.length === 0 ) return ; // No result

			var ids = [] ;
			var q = [] ;
			var h = '<div id="wdsearch_container">' ;
			h += '<h3>' ;
			h += i18n[i18n_lang].header ;
			h += '</h3><table><tbody>' ;
			$.each ( d.query.search , function ( k , v ) {
				q.push ( v.title ) ;
				var title = [] ;
				var snip = $('<span>'+v.snippet+'</span>') ;
				$.each ( snip.find('span.searchmatch') , function ( a , b ) {
					var txt = $(b).text() ;
					if ( -1 != $.inArray ( txt , title ) ) return ;
					title.push ( txt ) ;
				} );
				if ( title.length === 0 ) title = [ v.title ] ; // Fallback to Q
				ids.push ( v.title ) ;
				h += '<tr id="' + v.title + '">' ;
				h += '<th><a class="wd_title" href="//www.wikidata.org/wiki/' + v.title + '">' + title.join ( ' ' ) + '</a></th>' ;
				h += '<td><span class="wd_desc"></span><span class="wd_manual_desc"></span></td>' ;
				h += '<td nowrap>' ;
				h += '<span class="wikipedia"></span>' ;
				h += '<span class="commonscat"></span>' ;
				h += '<span class="wikivoyage"></span>' ;
				h += '<span class="wikisource"></span>' ;
				var rs = i18n[i18n_lang].reasonator ;
				if ( rs === undefined ) rs = i18n.en.reasonator ;
				h += ' <a title="'+rs+'" href="//tools.wmflabs.org/reasonator/?lang='+ i18n_lang +'&q='+v.title+'"><img src="//upload.wikimedia.org/wikipedia/commons/thumb/e/e8/Reasonator_logo_proposal.png/16px-Reasonator_logo_proposal.png" border=0/></a>' ;
				h += '</td>' ;
				h += '</tr>' ;
			});
			h += '</tbody></table>' ;
			h += '</div>' ;


			if ( mode == 'searchresults' ) {
				$('#mw-content-text').append ( h ) ;
			} else if ( mode == 'noarticletext' ) {
				$('div.noarticletext').after ( h ) ;
			}

			if ( ids.length === 0 ) return ;

			$.getJSON ( api , {
				action:'wbgetentities',
				ids:ids.join('|'),
				format:'json',
				languages:i18n_lang
			} , function ( d ) {
				var h;
				if ( d === undefined || d.entities === undefined ) return ; // Some error
				$.each ( d.entities , function ( q , v ) {

					if ( v.claims && undefined !== v.claims.P373 ) { // Commons cat
						var cat = v.claims.P373[0].mainsnak.datavalue.value ;
						h = ' <a title="'+i18n[i18n_lang].commons_cat+'" href="//commons.wikimedia.org/wiki/Category:'+mw.util.wikiUrlencode(cat)+'"><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/4/4a/Commons-logo.svg/12px-Commons-logo.svg.png" border=0 /></a>' ;
						$('#'+q+' span.commonscat').html ( h ) ;
					}

					if ( undefined !== v.labels && undefined !== v.labels[i18n_lang] ) { // Label
						h = v.labels[i18n_lang].value ;
						$('#'+q+' a.wd_title').html ( h ) ;
					}

					if ( undefined !== v.descriptions && undefined !== v.descriptions[i18n_lang] ) { // Manual desc
						h = '; ' + v.descriptions[i18n_lang].value ;
						$('#'+q+' span.wd_manual_desc').html ( h ) ;
					}

					if ( undefined !== v.sitelinks ) { // Wikipedia links
						var wikis = { wikipedia:[] , wikivoyage:[] , wikisource:[] } ;
						$.each ( v.sitelinks , function ( site , v2 ) {
							var m = site.match ( /^(.+)wiki$/ ) ;
							if ( null !== m  ) {
								wikis.wikipedia.push ( { site:site , title:v2.title , url:'//'+m[1]+'.wikipedia.org/wiki/'+mw.util.wikiUrlencode(v2.title) } ) ;
								return ;
							}
							m = site.match ( /^(.+)wikivoyage$/ ) ;
							if ( null !== m  ) {
								wikis.wikivoyage.push ( { site:site , title:v2.title , url:'//'+m[1]+'.wikivoyage.org/wiki/'+mw.util.wikiUrlencode(v2.title) } ) ;
								return ;
							}
							m = site.match ( /^(.+)wikisource$/ ) ;
							if ( null !== m  ) {
								wikis.wikisource.push ( { site:site , title:v2.title , url:'//'+m[1]+'.wikisource.org/wiki/'+mw.util.wikiUrlencode(v2.title) } ) ;
								return ;
							}
						} ) ;
						var icons = {
							wikipedia:'https://upload.wikimedia.org/wikipedia/commons/thumb/8/80/Wikipedia-logo-v2.svg/14px-Wikipedia-logo-v2.svg.png' ,
							wikivoyage:'https://upload.wikimedia.org/wikipedia/commons/thumb/8/8a/Wikivoyage-logo.svg/14px-Wikivoyage-logo.svg.png' ,
							wikisource:'https://upload.wikimedia.org/wikipedia/commons/thumb/4/4c/Wikisource-logo.svg/14px-Wikisource-logo.svg.png'
						} ;
						$.each ( [ 'wikipedia' , 'wikivoyage' , 'wikisource' ] , function ( k0 , v0 ) {
							if ( wikis[v0].length > 0 ) {
								var link_title = i18n[i18n_lang][v0+'s'] || v0 ;
								h = ' <a title="'+link_title+'" href="#"><img src="'+icons[v0]+'" border=0 /></a>' ;
								$('#'+q+' span.'+v0).html ( h ) ;
								$('#'+q+' span.'+v0+' a').click ( function () {
									var did = 'wdsearch_dialog_'+v0 ;
									$('#'+did).remove() ; // Cleanup
									h = '<div title="'+link_title+'" id="'+did+'"><div style="overflow:auto;max-height:500px">' ;
									h += '<table class="table table-condensed table-striped">' ;
									h += '<thead><tr><th>Site</th><th>Page</tr></thead><tbody>' ;
									$.each ( wikis[v0] , function ( k , v3 ) {
										h += '<tr><td>' + v3.site + '</td><td>' ;
										h += '<a href="'+v3.url+'">' + v3.title + '</a>' ;
										h += '</td></tr>' ;
									} ) ;
									h += '</tbody></table>' ;
									h += '</div></div>' ;
									$('#wdsearch_container').prepend ( h ) ;
									$('#'+did).dialog ( {
										modal:true
									} );
									return false ;
								} ) ;
							}
						} ) ;
					}

				} ) ;
			} ) ;

			var the_project = mw.config.get( 'wgSiteName' ).toLowerCase() ;
			if ( the_project == 'wikimedia commons' ) the_project = 'wikipedia' ;
			$.each ( q , function ( k , v ) {
				wd_auto_desc.loadItem ( v , {
					target:$('#'+v+' span.wd_desc') ,
					links : the_project ,
//					callback : function ( q , html , opt ) { mw.log ( q + ' : ' + html ) } ,
//					linktarget : '_blank'
				} ) ;
			});

		});
	}

	mw.loader.using( ['jquery.ui.dialog'], run );
});

} )( jQuery, mediaWiki );