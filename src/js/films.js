function main() {
    
    var monterHaut = document.getElementById('fleche');

    monterHaut.addEventListener("click", function() {
        window.scrollTo({
            top: 0, //remonte en haut
            behavior: 'smooth' //de manière douce
        });
    });

}

main();