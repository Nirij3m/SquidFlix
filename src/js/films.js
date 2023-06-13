// ------- READ FILE -------
function readFileByName(fileName){

    //console.log(window.location.pathname);

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

function readFile(src1, src2){ //src1 et src2 pour pouvoir utiliser la fonction plusieurs fois
    readFileByName(src1);
    return readFileByName(src2);
}

var nbr_max = 24; //nombre max d'élément par page
var first = 0; //indice de départ
var nbr_element = 0; //nombre d'élément chargé

function results(txt){

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

                            let randomImage = 'https://source.unsplash.com/random/?Films/' + Math.random(); //Obtention d'une image aléatoire

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

    let n = txt.length ; //taille du texte
    let count = 0 ; //pour savoir si on est en train d'écrire le nom ou le nombre de film
    let counter = 0; //pour le nombre de ligne

    let exe = ""; //temps d'execition + lettre
    let director = ""; //nom du director
    let film = ""; //nombre de film du director

    for ( let i = 0 ; i < n ; i ++ ){
        
        if ( counter == 1 || counter == 0){ //si ligne 1 ou 2 ( lettre + temps d'execution)
            if ( txt[i] != "\n"){
                exe += txt[i] ;
            }
            if (  txt[i] == "\n"){
                counter += 1 ;
            }
        }
        else { // signe 3 avec le nom du director et son nombre de film
            // count = 0 -> nom du directeur
            // count = 1 -> nombre de film
            if ( count == 0 && txt[i] != "\n" && txt[i] != ";"){
                director += txt[i] ; //Concaténation pour réccupérer le nom du director
            }
            if ( count == 1 && txt[i] != "\n" && txt[i] != ";"){
                film += txt[i] ;//Concaténation pour réccupérer le nombre de film du director
            }
            if ( txt[i] == ";" ){ // ; alors changement de champ
                count = ( count + 1 ) % 2 ;
            }
            if ( txt[i] == "\n" || i == ( n - 1 ) ){ //si retour ou fin du fichier

                // Pour avoir une majuscule ( mise en page )
                let size = director.length ;
                let director2 = "";
                for( let i = 0 ; i < size ; i ++ ){
                    if ( i == 0 ){
                        director2 += director[i].toUpperCase();
                    }
                    else{
                        director2 += director[i].toLowerCase();
                    }
                }
                //console.log(director2);
                // Mise en page

                document.getElementById("top-director").innerHTML = director2 ; //Ajoute le nom du real dans la balise top director
                document.getElementById("top-number").innerHTML = film ; //Ajoute le nombre de film du real dans la balise top number
            }
        }
    }
}


// Se déplacer dans la pagination
function firstPage(){
    first = 0; //On retourne à la première page
    results(readFile("/src/c/cmake-build/debug/ready4.txt","/src/c/cmake-build-debug/res_allFilms.txt"));
}

function previous(){
    //if(first + nbr_max <= nbr_element)             // Condition pour éviter de dépasser
    first+=nbr_max; //décale de +24 la position initiale
    results(readFile("/src/c/cmake-build/debug/ready4.txt","/src/c/cmake-build-debug/res_allFilms.txt"));
}

function nextPage(){
    if(first - nbr_max >= 0){
        first+=nbr_max; //décale de -24 la position initiale
        results(readFile("/src/c/cmake-build/debug/ready4.txt","/src/c/cmake-build-debug/res_allFilms.txt"));
    }
}


//let maxPages = Math.ceil(nbr_element / nbr_max);   // Nombre maximum du page générable
function lastPage(){
    //first = (maxPages * nbr_max) - nbr_max;        // Indice de la dernière position
    //Results(readFile("/src/c/cmake-build/debug/ready4.txt","/src/c/cmake-build-debug/res_allFilms.txt"));
}


/////////////////////////////////////////////////////////////////////////////////////////////::

function main() {

    topDirector(readFile("/src/c/cmake-build-debug/ready0.txt","/src/c/cmake-build-debug/res_director.txt")); //Lancement au démarage

}

main();