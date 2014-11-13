$(function(){
    //header 2
	var h2 = $("h2");
	h2.click(function(){
        $(this).animate({paddingLeft:"70%"},"slow","swing",function(){
            $(this).animate({paddingLeft:""},"slow" );}
        );
	});

    //header 3
	var h3 = $("h3");
	h3.mouseover(function() {
        $(this).animate({paddingLeft:"40%"},"fast","swing",function(){
            $(this).animate({paddingLeft:"50%"},"fast" );}
        );
	});

    //content list
    var toc = $(".toc");
    var contents = $("#hbottom #Contents");
    toc.hide();
    contents.click(function() {
        if (toc.length > 0) {
            toc.toggle('fast');
            return false;
        }
        else {
            $("#htop").toggle('fast');
        }
    });

    //Times is getting Fewer and Fewer.
    setInterval(function(){
        $('#Times').html(moment().format('MMMM Do YYYY, H:mm:ss Z'));
    },300);

});
