function animateCards(){
    console.log("updated");
    Array.from(document.getElementsByClassName("card-box")).forEach((card) => {
        console.log(card);
        card.addEventListener("mouseover", () => { //Je over la card
            console.log("over");
            card.children[0].classList.add("fade-in-bg");
            card.children[1].classList.add("fade-in-bg");
            card.getElementsByClassName("title")[0].style.color = "#c99e29";
            card.getElementsByClassName("genre")[0].style.color = "#ffffff";
            card.getElementsByClassName("duration")[0].style.color = "#4c4c4c";
            card.getElementsByClassName("genre")[0].style.color = "#595959";

        });
        card.addEventListener("mouseout", () => { //Je quitte la card
            card.children[0].classList.remove("fade-in-bg");
            card.children[1].classList.remove("fade-in-bg");
            card.getElementsByClassName("title")[0].style.color = "#f1f1f1";
            card.getElementsByClassName("genre")[0].style.color = "#f1f1f1";
            card.getElementsByClassName("duration")[0].style.color = "#f1f1f1";
            card.getElementsByClassName("genre")[0].style.color = "#f1f1f1";
        });
    });
}


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



// ------- ALL FILMS -------

///////////////////////////////////////////////////////////////////////:
// Variable globale (obligatoire car elles sont utilisées dans plusieurs fonctions)

var nbr_max = 24; //nombre max d'élément par page
var first = 0; //indice de départ
var nbr_element = ""; //nombre d'élément chargé
var tabInformationEachCard = []; //Tableau qui contriendra des tableaux donnant les informations de chaque carte

///////////////////////////////////////////////////////////////////////:

function results(txt){

    let n = txt.length ; //Taille
    let count = 0 ; //compteur pour savoir ce que nous écrivons (titre, time, genre)
    let counter = 0; //compteur pour la ligne
    let tabInformationCard = []; //Tableau qui contient les informations sur une carte

    let lettre = ""; //Pour savoir où écrire
    let exe = ""; //Temps d'exécution
    let titre = ""; //Le titre du film
    let time = ""; //La durée du film
    let genre = ""; //Le genre du film

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
                if ( count == 0 && txt[i] != "\n" && txt[i] != ";"){ //Titre du film
                    titre += txt[i] ;
                    //console.log("titre :" + titre)
                }
                if ( count == 1 && txt[i] != "\n" && txt[i] != ";"){ //Durée du film
                    time += txt[i] ;
                    //console.log("durée :" + time)
                }
                if ( count == 2 && txt[i] != "\n" && txt[i] != ";"){ //Genre du film
                    genre += txt[i] ;
                    //console.log("genre :" + genre)
                }
                if ( txt[i] == ";" ){ //On change de champ
                    count = ( count + 1 ) % 3 ;
                }
                if ( txt[i] == "\n" || i == ( n - 1 ) ){

                    count = 0 ; //On retourne au premier champ

                    tabInformationCard.push(titre, genre, time); //On ajoute les informations de la carte dans un tableau

                    tabInformationEachCard.push(tabInformationCard); //On ajoute le tableau de la carte dans un tableau
                    tabInformationCard = []; //On vide notre tableau d'information sur la carte pour boucler

                    titre = ""; //On vide l'information du titre pour boucler
                    time = ""; //On vide l'information de la durée pour boucler
                    genre = ""; //On vide l'information du genre pour boucler
                }
            }
        }
        
    }

                      
}

function showCard(){
    //-------------------------------------------------------------------------------------------
    // On remet notre carte comme model
    document.getElementsByClassName("container")[0].innerHTML = `<div class="card-box" id="hidden">
        <header class="cardHeader">
            <p></p>
            <p class="title">TITRE</p>
            <p class="genre">GENRE</p>
        </header>

        <footer class="cardFooter">
            <p class="duration">160min</p>
        </footer>
        <img class="backgroundImage" src=""></div>`;
    //-------------------------------------------------------------------------------------------

    for(let j = first; j < first + nbr_max; j++){ //Parcourt les cartes par indice en fonction de la valeur de first
        if(j < nbr_element){
            let newCard = document.getElementsByClassName("card-box")[0].cloneNode(true); //Clone la carte modèle
            newCard.id = "";
            newCard.children[0].children[1].innerHTML = tabInformationEachCard[j][0] ; //Renseigne le titre dans la carte
            newCard.children[0].children[2].innerHTML = tabInformationEachCard[j][1] ; //Renseigne le genre dans la carte
            newCard.children[1].children[0].innerHTML = tabInformationEachCard[j][2] ; //Renseigne la durée dans la carte

            let randomImage = 'https://source.unsplash.com/random/?Films/' + Math.random(); //Obtention d'une image aléatoire

            newCard.children[2].setAttribute("src", randomImage);

            document.getElementsByClassName("container")[0].appendChild(newCard); //ajoute la carte sur la page
            //tabInformationEachCard.forEach((elt) => console.log(elt[0] + " : " + elt[1] + " (" + elt[2] + ")"));
        }
    }
    animateCards();
}


// Se déplacer dans la pagination
function firstPage(){
    first = 0; //On retourne à la première page
    //console.log(first);
    showCard(); 
}

function nextPage(){
    if(first + nbr_max <= nbr_element){ // Condition pour éviter un dépassement
        first += nbr_max; //décale de -24 la position initiale
        //console.log(first);
        showCard();
    }
}

function previous(){
    if(first - nbr_max >= 0){ // Condition pour éviter un dépassement
        first -= nbr_max; //décale de +24 la position initiale
        //console.log(first);
        showCard();
    }
}

function lastPage(){
    let maxPages = Math.ceil(nbr_element / nbr_max);   // Nombre maximum du page générable
    first = (maxPages * nbr_max) - nbr_max;        // Indice de la dernière position
    //console.log(first);
    showCard();
}



// ------- TOP DIRECTOR -------

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


/////////////////////////////////////////////////////////////////////////////////////////////:

function main() {

    topDirector(readFile("src/c/cmake-build-debug/ready0.txt","src/c/cmake-build-debug/res_director.txt")); //Lancement au démarage
    results(readFile("src/c/cmake-build-debug/ready4.txt","src/c/cmake-build-debug/res_allFilms.txt"));
    //results(readFile("src/js/ready3.txt","src/js/BD_small.txt"));
    showCard();

}
animateCards()
main();