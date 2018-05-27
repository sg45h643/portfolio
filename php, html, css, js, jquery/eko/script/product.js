$(document).ready(function(){ 
			
		$('.product a').hide();
	
		$('.product a:eq(0)').addClass('active').show();				
						
		setInterval(function()
   {
       var now = $('.product .active');
       now.removeClass('active').hide(); 
               
        if( now.next().length )
           now.next().addClass('active').show();
       else
           $('.product a:eq(0)').addClass('active').show();
           
   }, 5000);
					
});