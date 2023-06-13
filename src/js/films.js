// ------- READ FILE -------
function readFileByName(fileName){

    console.log(window.location.pathname);

    //console.log("poulpe");

    let xhr = new XMLHttpRequest();
    do {
        xhr.open("GET", fileName, false);
        xhr.send(null);
        //console.log("bloup");

    }while(xhr.status === 404);

    // assumes status 200
    //console.log(xhr.responseText)
    //console.log("octopus");
    return xhr.responseText;
}

function readFile(src1, src2){
    readFileByName(src1);
    return readFileByName(src2);
}

var nbr_max = 24; //nombre max d'élément par page
var first = 0; //indice de départ
var nbr_element = 0; //nombre d'élément chargé

function results(){

    let n = txt.length ;
    let count = 0 ;
    let counter = 0;

    let exe = "";
    let titre = "";
    let time = "";
    let genre = "";

    if ( txt == "NULL"){

        let p = document.createElement('p').innerHTML = "Film introuvable..." ;
        document.getElementsByClassName("container")[0].appendChild(p);

    }
    else {
        for ( let i = 0 ; i < n ; i ++ ){
            if ( counter == 0 && txt[i] != "\n"){
                exe += txt[i] ;
            }
            if ( counter == 0 && txt[i] == "\n"){
                counter += 1 ;
            }
            else {
                if ( count == 0 && txt[i] != "\n" && txt[i] != ";"){
                    titre += txt[i] ;
                }
                if ( count == 1 && txt[i] != "\n" && txt[i] != ";"){
                    time += txt[i] ;
                }
                if ( count == 2 && txt[i] != "\n" && txt[i] != ";"){
                    genre += txt[i] ;
                }
                if ( txt[i] == ";" ){
                    count = ( count + 1 ) % 3 ;
                }
                if ( txt[i] == "\n" || i == ( n - 1 ) ){

                    count = 0 ;
                    nbr_element+=1; // + une carte sur la page

                    for(let j = first; j < first + nbr_max; j++){
                        if(j < nbr_element){

                            let newCard = document.getElementsByClassName("container")[1].cloneNode(true);
                            console.log(newCard);
                            newCard.children[0].children[0].children[1].innerHTML = titre ;
                            newCard.children[0].children[0].children[2].innerHTML = genre ;
                            newCard.children[0].children[1].children[0].innerHTML = time ;

                            let randomImage = 'https://source.unsplash.com/random/?Octopus/' + Math.random(); //Obtention d'une image aléatoire

                            newCard.children[0].children[2].setAttribute("src", randomImage);

                            document.getElementsByClassName("container")[0].appendChild(newCard); //ajoute la carte sur la page

                            titre = "";
                            time = "";
                            genre = "";
                        }
                    }
                }
            }
        }
    }
}

function topDirector(txt){

    let n = txt.length ;
    let count = 0 ;
    let counter = 0;

    let exe = "";
    let director = "";
    let film = "";

    for ( let i = 0 ; i < n ; i ++ ){
        
        if ( counter == 0 && i > 1 ){
            if ( txt[i] != "\n"){
                exe += txt[i] ;
                console.log("exe : " + exe);
            }
            if (  txt[i] == "\n"){
                counter += 1 ;
            }
        }
        else {
            if ( count == 0 && txt[i] != "\n" && txt[i] != ";"){
                director += txt[i] ;
                console.log("director : " + director);
            }
            if ( count == 1 && txt[i] != "\n" && txt[i] != ";"){
                film += txt[i] ;
                console.log("film : " + film);
            }
            if ( txt[i] == ";" ){
                count = ( count + 1 ) % 2 ;
            }
            if ( txt[i] == "\n" || i == ( n - 1 ) ){
                document.getElementById("top-director").innerHTML = director ;
                document.getElementById("top-number").innerHTML = film ;
            }
        }
    }
}


// Se déplacer dans la pagination
function firstPage(){
    first = 0; //On retourne à la première page
    results(readFile());
}

function previous(){
    //if(first + nbr_max <= nbr_element)             // Condition pour éviter de dépasser
    first+=nbr_max; //décale de +24 la position initiale
    results(readFile());
}

function nextPage(){
    if(first - nbr_max >= 0){
        first+=nbr_max; //décale de -24 la position initiale
        results(readFile());
    }
}


//let maxPages = Math.ceil(nbr_element / nbr_max);   // Nombre maximum du page générable
function lastPage(){
    //first = (maxPages * nbr_max) - nbr_max;        // Indice de la dernière position
    //Results(readFile());
}


/////////////////////////////////////////////////////////////////////////////////////////////::

function main() {
    
    var monterHaut = document.getElementById('fleche');

    monterHaut.addEventListener("click", function() {
        window.scrollTo({
            top: 0, //remonte en haut
            behavior: 'smooth' //de manière douce
        });
    });

    topDirector(readFile());

}

main();