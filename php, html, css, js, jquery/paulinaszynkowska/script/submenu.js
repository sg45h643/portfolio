$(document).ready(function() {
	$('#submenu').hide();
	$('#submenu, #psychotherapy').hover(
	   function() { $('#submenu').show(); $('#psychotherapy').addClass('psychotherapy-hover'); }, 	
	   function() { $('#submenu').hide(); $('#psychotherapy').removeClass('psychotherapy-hover');}
	 );
});