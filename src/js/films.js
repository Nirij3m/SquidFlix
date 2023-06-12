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

function readFile(){
    readFileByName("/src/c/cmake-build-debug/ready.txt");
    return readFileByName("/src/c/cmake-build-debug/results.txt");
}

var nbr_max = 24; //nombre max d'élément par page
var first = 0; //indice de départ
var nbr_element = 0; //nombre d'élément chargé


function Results(txt){

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

            document.getElementById("title").innerHTML = exe ;

        }

        //console.log(exe);
        //console.log(titre);
        //console.log(time);
        //console.log(genre);
        //console.log(movies);
        //console.log(film);

    }
}


// Se déplacer dans la pagination
function firstPage(){

}

function previous(){
    //first+=nbr_max; //décale de 24 la position initiale
    //Results(readFile());
}

function nextPage(){
    
}

function lastPage(){
    
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

    Results(readFile());

}

main();