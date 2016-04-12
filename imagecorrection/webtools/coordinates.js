$(function(){
    // updates coordinates
    $('#image').mousemove(function(e){
        var offset = $(this).offset();
        $('#coordvals').html('Coordinates: x: ' + (e.pageX - offset.left) + ' y : ' + (1944 - (e.pageY - offset.top)));
    });
    
    // updates the image src
    $('#image-name').change(function() {
        $('#image').attr('src', '../../images/' + $(this).val());
    });
})