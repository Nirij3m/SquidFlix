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
var nbr_element = ""; //nombre d'élément chargé
var tabInformationEachCard = [];

function results(txt){

    let n = txt.length ;
    let count = 0 ;
    let counter = 0;
    let tabInformationCard = [];

    let lettre = ";"
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
            if (counter === 0 || counter === 1 || counter === 2){ //Une des 3 premières lignes
                if ( counter === 0 && txt[i] != "\n"){ //lettre pour savoir où écrire le txt[i=0]
                    lettre += txt[i];
                }

                if ( counter === 1 && txt[i] != "\n"){ //temps d'éxécution
                    exe += txt[i] ;
                    //console.log("exe : " + exe);
                }

                if ( counter === 2 && txt[i] != "\n"){ //nombre de films
                    nbr_element+= txt[i] ;
                    //console.log("exe : " + exe);
                }

                if ( txt[i] == "\n"){//On change de ligne
                    counter += 1 ;
                }
            }
            else {
                if ( count == 0 && txt[i] != "\n" && txt[i] != ";"){
                    titre += txt[i] ;
                    //console.log("titre :" + titre)
                }
                if ( count == 1 && txt[i] != "\n" && txt[i] != ";"){
                    time += txt[i] ;
                    //console.log("durée :" + time)
                }
                if ( count == 2 && txt[i] != "\n" && txt[i] != ";"){
                    genre += txt[i] ;
                    //console.log("genre :" + genre)
                }
                if ( txt[i] == ";" ){
                    count = ( count + 1 ) % 3 ;
                }
                if ( txt[i] == "\n" || i == ( n - 1 ) ){

                    count = 0 ;

                    tabInformationCard.push(titre, genre, time);

                    tabInformationEachCard.push(tabInformationCard);
                    tabInformationCard = [];

                    titre = "";
                    time = "";
                    genre = "";
                }
            }
        }
        
    }

                      
}

function showCard(){
    //if(document.getElementsByClassName("container")[0].children.length > 0){
        //for(let k = 0; k < document.getElementsByClassName("container")[0].children.length; k++){
            //document.getElementsByClassName("container")[0].removeChild(k);
        //}

        //Array.from(document.getElementsByClassName("container")[0].children).forEach(function (element) {
            //document.getElementsByClassName("container")[0].removeChild(element);
        //});
    //}

    document.getElementsByClassName("container")[0].innerHTML = `<div class="card-box">
        <header class="cardHeader">
            <p></p>
            <p class="title">TITRE</p>
            <p class="genre">GENRE</p>
        </header>

        <footer class="cardFooter">
            <p class="duration">160min</p>
            <p class="director">DIRECTOR</p>
        </footer>
        <img class="backgroundImage" src=""></div>`;

    for(let j = first; j < first + nbr_max; j++){
        if(j < nbr_element){
            let newCard = document.getElementsByClassName("card-box")[0].cloneNode(true);

            newCard.children[0].children[1].innerHTML = tabInformationEachCard[j][0] ;
            newCard.children[0].children[2].innerHTML = tabInformationEachCard[j][1] ;
            newCard.children[1].children[0].innerHTML = tabInformationEachCard[j][2] ;

            let randomImage = 'https://source.unsplash.com/random/?Films/' + Math.random(); //Obtention d'une image aléatoire

            newCard.children[2].setAttribute("src", randomImage);

            document.getElementsByClassName("container")[0].appendChild(newCard); //ajoute la carte sur la page
            //tabInformationEachCard.forEach((elt) => console.log(elt[0] + " : " + elt[1] + " (" + elt[2] + ")"));
        }
    }
}


// Se déplacer dans la pagination
function firstPage(){
    first = 0; //On retourne à la première page
    //console.log(first);
    //results(readFile("src/c/cmake-build/debug/ready4.txt","src/c/cmake-build-debug/res_allFilms.txt"));
    //results(readFile("src/js/ready3.txt","src/js/BD_small.txt"));
    showCard();
}

function nextPage(){
    if(first + nbr_max <= nbr_element){
        first += nbr_max; //décale de -24 la position initiale
        //console.log(first);
        //results(readFile("src/c/cmake-build/debug/ready4.txt","src/c/cmake-build-debug/res_allFilms.txt"));
        //results(readFile("src/js/ready3.txt","src/js/BD_small.txt"));
        showCard();
    }
}

function previous(){
    if(first - nbr_max >= 0){            // Condition pour éviter de dépasser
        first -= nbr_max; //décale de +24 la position initiale
        //console.log(first);
        //results(readFile("src/c/cmake-build/debug/ready4.txt","src/c/cmake-build-debug/res_allFilms.txt"));
        //results(readFile("src/js/ready3.txt","src/js/BD_small.txt"));
        showCard();
    }
}

function lastPage(){
    let maxPages = Math.ceil(nbr_element / nbr_max);   // Nombre maximum du page générable
    first = (maxPages * nbr_max) - nbr_max;        // Indice de la dernière position
    //console.log(first);
    //Results(readFile("src/c/cmake-build/debug/ready4.txt","src/c/cmake-build-debug/res_allFilms.txt"));
    //results(readFile("src/js/ready3.txt","src/js/BD_small.txt"));
    showCard();
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


/////////////////////////////////////////////////////////////////////////////////////////////::

function main() {

    topDirector(readFile("src/c/cmake-build-debug/ready0.txt","src/c/cmake-build-debug/res_director.txt")); //Lancement au démarage
    //results(readFile("src/c/cmake-build/debug/ready4.txt","src/c/cmake-build-debug/res_allFilms.txt"));
    results(readFile("src/js/ready3.txt","src/js/BD_small.txt"));
    showCard();

}

main();