jQuery(document).ready(function() {
	jQuery(".carousel").carousel({
		interval: false
	});
	jQuery(".carousel").click(function(){
		jQuery(this).carousel('next');
		//alert(jQuery(this).height());
		//var height_pic = jQuery(this).height();
		//jQuery('#profile').affix({
		//	offset: height_pic 
		//});
	});
	//jQuery(".carousel img").addClass("img-polaroid");

	//jQuery('#content ul').addClass("hero-unit");
	//jQuery('#profile').affix({
	//	offset: 700 
	//});
	
	jQuery('h3').prepend('<i class="icon-th"></i><i class="icon-th"></i> ');
	//jQuery('h2').addClass('text-center');
	jQuery('h2').prepend('<i class="icon-th"></i>');

	jQuery('h3').next('ul').css('display', 'none');
	jQuery('h3').click(function(){
		jQuery(this).next('ul').fadeToggle();
	});
});
