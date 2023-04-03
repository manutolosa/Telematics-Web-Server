$( document ).ready(function(){
    $("#up").on("mousedown", function() {
     $.get('/adelante');
     }).on('mouseup', function() {
     $.get('/detener');
    });
    $( document ).ready(function(){
        $("#down").on("mousedown", function() {
         $.get('/atras');
         }).on('mouseup', function() {
         $.get('/detener');
        });
    });
    $( document ).ready(function(){
        $("#left").on("mousedown", function() {
         $.get('/izquierda');
         }).on('mouseup', function() {
         $.get('/detener');
        });
    });
    $( document ).ready(function(){
        $("#rigth").on("mousedown", function() {
         $.get('/derecha');
         }).on('mouseup', function() {
         $.get('/detener');
        });
    });
});

//grafica


