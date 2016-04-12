$(function(){
    var locked = false;
    
    // updates coordinates
    $('#image').mousemove(function(e){
        if (!locked) {
            var offset = $(this).offset();
            $('#coordvals').html('Coordinates: x: ' + (e.pageX - offset.left) + ' y : ' + (1944 - (e.pageY - offset.top)));
        }
    });
    
    // lock current position
    $('#image').click(function(){
        if (locked) {
            locked = false;
            $('#coordvals').removeClass('bold');
        } else {
            locked = true;
            $('#coordvals').addClass('bold');
        }
    });
    
    // updates the image src
    $('#image-name').change(function() {
        $('#image').attr('src', '../../images/' + $(this).val());
    });
})