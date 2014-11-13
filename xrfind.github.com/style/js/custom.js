(function($){
$(document).ready(function() {
	var toc = $('.toc a');
	var current_page_dd = $('#current-page-dd');
	toc.each(function(index) {
		var href = $(this).attr('href');
		var href_sp = href.substring(5).split(".").length;
		var cpd_last_li = current_page_dd.find('li:last-child');

		var str = "<li><a href='" + href + "'>";
		if (href_sp == 1) {
			str += "<strong>" + $(this).text() + "</strong>";
		}
		else if (href_sp == 2) {
			str += $(this).text();
		}
		str += "</a><li>";

		if (cpd_last_li.size() == 1 && href_sp < 3) {
			cpd_last_li.after(str)
		}
		else if(href_sp<3) {
			current_page_dd.append(str);
		}
	});

	$('.toc').hide();	
	
	$('#current-page').html('<strong>' + $('title').text() + '</strong>');

});
})(jQuery)
