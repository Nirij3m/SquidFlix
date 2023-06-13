//Modal liste Auteurs

// Get the modal
var modalQuestion = document.getElementById("Modal-question");

// Get the button that opens the modal
var btnQuestion = document.getElementById("fa-qst");

// Get the <span> element that closes the modal
var spanQuestion = document.getElementsByClassName("close-question")[0];

// When the user clicks the button, open the modal 
btnQuestion.onclick = function() {
    modalQuestion.style.display = "block";
}

// When the user clicks on <span> (x), close the modal
spanQuestion.onclick = function() {
    modalQuestion.style.display = "none";
}

// When the user clicks anywhere outside of the modal, close it
window.onclick = function(event) {
  if (event.target == modalQuestion) {
    modalQuestion.style.display = "none";
  }
}


//Ecriture dans un fichier
//Fonction pour réccupérer les valeurs entrer dans le form
function recup(){

    //console.log("octopus");

    let counter = "000" ; //si 000 alors rien d'entrée nul part
    // 0 si vide
    // 1 si remplis

    //console.log(counter);

    let director = document.getElementById("searchDirector").value; //On réccupère ce qui est dans director
    let size = director.length ;
    //console.log("length : " + size);
    //console.log(director);

    // Ajouter une majuscule au début - Mise en Page
    if(director != ''){
        let director2 = "";
        for( let i = 0 ; i < size ; i ++ ){
            if ( i == 0 ){
                director2 += director[i].toUpperCase(); //Mettre en Majuscule
            }
            else{
                director2 += director[i].toLowerCase(); //Mettre en minuscule
            }
        }
        //console.log(director2);
        document.getElementById("searchDirector").value = director2 ; //échange pour une meilleure lisibilité
    }
    //Mise en page

    let time = document.getElementById("searchTime").value; //Réccupérer les données dans seahTime
    //console.log(time);

    //Si valeur négative alors valeur absolu
    if(time < 0){
        let time2 = time * ( -1 ) ;
        
        document.getElementById("searchTime").value = time2 ;
    }
    //Si valeur négative

    let genre = document.getElementById("searchGenre").value;
    //console.log(genre);

    if(director == '' && time == "" && genre == "None"){ //Si rien de remplis
        counter = "000";
    }
    else {
        if(director != '' && time != "" && genre != "None"){ // si tout remplis
            counter = "111";
        }
        else {
            if(director != '' && time == "" && genre == "None"){ // si director seulement remplis
                counter = "100";
            }
            else {
                if(director == '' && time != "" && genre == "None"){ // si time seulement remplis
                    counter = "010";
                }
                else {
                    if(director == '' && time == "" && genre != "None"){ // si genre seulement remplis
                        counter = "001";
                    }
                    else {
                        if(director != '' && time != "" && genre == "None"){ //si director et time remplis
                            counter = "110";
                        }
                        else {
                            if(director != '' && time == "" && genre != "None"){ //si director et genre remplis
                                counter = "101";
                            }
                            else {
                                if(director == '' && time != "" && genre != "None"){ //si durer et genre remplis
                                    counter = "011";
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //console.log(counter);
    return counter ; // renvoie quelle champ est remplis par l'utilisateur
}

//Pour supprimer les cartes d'une ancienne demande par exemple
function clear(){

    card = document.getElementById("test1"); // On réccupère le code d'une carte par défaut
    document.getElementsByClassName("container1")[0].innerHTML = ""; // On supprime tout ce qu'il y a dans le container
    document.getElementsByClassName("container2")[0].innerHTML = ""; // On supprime tout ce qu'il y a dans le container
    document.getElementsByClassName("container1")[0].appendChild(card); //On re-ajoute la carte ( pour recommencer )
    document.getElementsByClassName("container2")[0].appendChild(card); //On re-ajoute la carte ( qui est invisible car display : none )

}

// ------- WRITE FILE -------
function writeFile(counter, id_form,func, destionnation) {

    //console.log("Poulpe");

    var element = document.createElement('a'); //creation d'une balise <a>
    let save = ""; //Texte à mettre dans le fichier
    //console.log(save);
    //console.log("element : " + element);

    for(let j = 0; j < counter ; j ++){ //Boucle si multifiltre pour faire toutes les demande

        //console.log("id_form : " + id_form[j]);

        let text1 = document.getElementById(id_form[j]).value; //octenir les valeurs dans le form
        //console.log("text : " + text1);

        let count = text1.length; //taille
        //console.log("count : " + count);

        //console.log(func[j]);
        let textToSave = destionnation + ";" + func[j] + ";";
        //console.log(textToSave);

        for(let i = 0;i<=count-1;i++){ //ecriture
            textToSave += text1[i];
            //console.log("TextToSave_1 : " + textToSave);
            //console.log("text1[i] : " + text1[i]);
        }

        save += textToSave + "\n" //retour à la ligne
        //console.log(save);
    }

    //console.log(save);

    element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(save));
    element.setAttribute('download', 'request.txt');

    element.style.display = 'none';
    document.body.appendChild(element);
    element.click();
    document.body.removeChild(element);

   // text1.submit();
}
// ------- WRITE FILE -------

function find(){ //Pour lancer la fonction écriture

    let counter = recup(); // pour savoir qu'elle champ est remplis

    clear(); // pour supprimer si il y avait une recheche avant

    if ( counter == "000" ){ //vide
        console.log("Veuillez entrez quelque chose avant de rechercher\nPour voir l'intégralité de notre catalogue vous pouvez aller dans la catégorie Films.")
        return;
    }
    else{
        if ( counter == "100" ){
            writeFile(1,['searchDirector'],["findByDirector"], "R"); //Le champ Directeur est rempli
        }
        else {
            if ( counter == "010" ){
                writeFile(1,['searchTime'],["findByDuration"], "R"); //Le champ Durée est rempli
            }
            else{
                if ( counter == "001" ){
                    writeFile(1,['searchGenre'],["findByGenre"], "R"); //Le champ Genre est rempli
                }
                else{
                    if ( counter == "110" ){
                        writeFile(2,['searchDirector','searchTime'],["findByDirector","findByDuration"], "R"); //Les champs Directeur et Durée sont remplis
                    }
                    else{
                        if ( counter == "101" ){
                            writeFile(2,['searchDirector','searchGenre'],["findByDirector","findByGenre"], "R"); //Les champs Directeur et Genre sont remplis
                        }
                        else{
                            if ( counter == "011" ){
                                writeFile(2,['searchTime','searchGenre'],["findByDuration","findByGenre"], "R"); //Les champs Durée et Genre sont remplis
                            }
                            else{
                                if ( counter == "111" ){
                                    writeFile(3,['searchDirector','searchTime','searchGenre'],["findByDirector","findByDuration","findByGenre"], "R"); //Tous les champs sont remplis
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}

// ------- READ FILE -------
function readFileByName(fileName){

    //console.log(window.location.pathname); // pour savoir où on se trouve

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

function readFile(src1, src2){ // src1 et src2 pour choisir ce qu'on va chercher et pas avoir une fonction à usage unique
    readFileByName(src1);
    return readFileByName(src2);
}
// ------- READ FILE -------

function results(txt){

    let n = txt.length ; // taille
    let count = 0 ; //compteur pour savoir ce que nous écrivons ( lettre, exe, director...)
    let counter = 0; //compteur pour le nombre de ligne
    let suggestion = 1 ; //Pour lancer la suggestion

    let lettre = ""; //Pour savoir où écrire
    let exe = ""; //Temps d'exécution
    let director = ""; //Nom du directeur
    let titre = ""; //Titre du film
    let time = ""; //Durer du film
    let genre = ""; //Genre du film

    for ( let i = 0 ; i < n ; i ++ ){ //Boucle pour avoir lettre par lettre
        
        if ( counter === 1 || counter === 0 ){ //Une des 2 premières ligne
            if ( counter === 0 && txt[i] != "\n"){ //lettre pour savoir où écrire c'est txt[i=0]
                lettre += txt[i];
            }
            if ( counter === 1 && txt[i] != "\n"){ //Temps d'exe
                exe += txt[i] ;
                //console.log("exe : " + exe);
            }
            if ( txt[i] == "\n"){//On change de ligne
                counter += 1 ;
            }
        }
        else {            //On commence à lire des lignes avec les films
            if ( count == 0 && txt[i] != "\n" && txt[i] != ";"){ //Nom du directeur
                director += txt[i] ;
                //console.log("director : " + director);
            }
            if ( count == 1 && txt[i] != "\n" && txt[i] != ";"){ //Titre du film
                titre += txt[i] ;
                console.log("titre : " + titre);
            }
            if ( count == 2 && txt[i] != "\n" && txt[i] != ";"){ //durer du film
                time += txt[i] ;
                console.log("time : " + time);
            }
            if ( count == 3 && txt[i] != "\n" && txt[i] != ";"){ //genre du film
                genre += txt[i] ;
                console.log("genre : " + genre);
            }
            if ( txt[i] == ";" ){ //on change de champ
                count = ( count + 1 ) % 4 ;
            }
            if ( txt[i] == "\n" || i == ( n - 1 ) ){//Retour à la ligne ou fin du texte, on imprime car fin du film 

                count = 0 ; //On remet le count à 0 pour être sur

                if ( txt[0] === "R"){ //Si c'est pour réponse

                    if ( suggestion === 1 ){ //Première carte de film
                        document.getElementById("searchGenre2").value = genre ; //On choisis le genre du premier film
                        //writeFile(1,['searchGenre2'],["findByGenre"], "S"); //On renvoie une seconde requetes
                        suggestion += 1 ; //On met suggestion à 2 pour être sur de le faire qu'une fois
                    }

                    let newCard = document.getElementsByClassName("card-box1")[0].cloneNode(true); //On clone une nouvelle carte pour faire pareil
                    newCard.id =""; //Id à rien, car sinon display none
                    //console.log(newCard);

                    // Pour avoir une majuscule ( mise en page )
                    let size = director.length ; //taille
                    let director2 = ""; //vide
                    for( let i = 0 ; i < size ; i ++ ){
                        if ( i == 0 ){
                            director2 += director[i].toUpperCase(); //Majuscule
                        }
                        else{
                            director2 += director[i].toLowerCase(); //minuscule
                        }
                    }
                    //console.log(director2);
                    // Mise en page

                    newCard.children[0].children[1].innerHTML = titre ; //On insert les informations du film
                    newCard.children[0].children[2].innerHTML = genre ; //On insert les informations du film
                    newCard.children[1].children[0].innerHTML = time ; //On insert les informations du film
                    newCard.children[1].children[1].innerHTML = director ; //On insert les informations du film

                    let randomImage = 'https://source.unsplash.com/random/?Squid/' + Math.random(); //Obtention d'une image aléatoire

                    newCard.children[2].setAttribute("src", randomImage); //On change le src pour avoir une image random 

                    document.getElementsByClassName("container1")[0].appendChild(newCard); //On ajoute la nouvelle card
                    //console.log("bloup");

                    document.getElementsByClassName("exe").innerHTML = exe ;
                }

                if ( txt[0] === "S"){ //Si c'est pour une suggestion

                    let newCard = document.getElementsByClassName("card-box2")[0].cloneNode(true); //On créer un clone pour ajouter des cartes de films
                    newCard.id =""; //Id à vide pour pas avoir de display none
                    //console.log(newCard);

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

                    newCard.children[0].children[1].innerHTML = titre ; //On insert les informations du film
                    newCard.children[0].children[2].innerHTML = genre ; //On insert les informations du film
                    newCard.children[1].children[0].innerHTML = time ; //On insert les informations du film
                    newCard.children[1].children[1].innerHTML = director ; //On insert les informations du film

                    let randomImage = 'https://source.unsplash.com/random/?Octopus/' + Math.random(); //Obtention d'une image aléatoire

                    newCard.children[2].setAttribute("src", randomImage); //On change le src afin d'avoir une image aléatoire pour chaque film

                    document.getElementsByClassName("container2")[0].appendChild(newCard); //On ajoute la carte au container pour l'affihcer
                    //console.log("bloup");

                }

                titre = "" ; //Réinitalisation des champs
                time = "" ; //Réinitalisation des champs
                genre = "" ; //Réinitalisation des champs
                director = ""; //Réinitalisation des champs
            }
        }
    }
}


function directorName(txt){
    let n = txt.length; //taille du texte
    let directors = ""; //contient chaque directeur
    console.log("accesesed");
    let newItem = document.getElementsByClassName("listAuthor")[0].cloneNode(true); //Clone la balise <p> qui contient chaque directeur et la stocke dans newItem

    for(let i = 0; i < n; i++){ //parcourt chaque lettre du fichier

        if(txt[0] === "D" && txt[i] != "\n" && i>1){ //Vérifie si c'est un caractère
            directors += txt[i];
            //console.log("réalisateur : " + directors);
        }

        if(txt[0] === "D" && txt[i] == "\n" && i>1){//Vérifie si c'est un retour à la ligne => fin du nom du directeur
            newItem.innerHTML = directors; //Valeur dans la balise dans le HTML
            document.getElementsByClassName("listAuthor")[0].parentNode.appendChild(newItem); //ajoute le newItem
        }
        directors = "";
    }
}


// -------------------------

// -------------------------

function search(){

    //console.log("poulpe");

    find();//lance la fonction pour voir si on peut lancer l'écriture

    let counter = recup();
    if ( counter !== "000"){ // si au moins un champ est remplis

        //readFile();
        let myresults = readFile("src/c/cmake-build-debug/ready.txt", "src/c/cmake-build-debug/results.txt"); //on réccupère les résultats de la fonction readFile
        //console.log(myresults);

        results(myresults); // Fonction pour l'affichage des résultats
        setTimeout(() =>{}, "1000"); //pause

        let Sug = readFile("src/c/cmake-build-debug/ready.txt", "src/c/cmake-build-debug/results.txt"); //On réccupère les résultats pour faire une suggestion à partir du genre du premier film resortie
        //console.log(Sug);

        results(Sug); //On affiche
    }
    else{
        alert("Champ(s) vide(s)!") //Si champ vide une alert car on peut pas chercher
    }
}

function main(){
    directorName(readFile("src/c/cmake-build-debug/ready4.txt", "src/c/cmake-build-debug/res_allDirector.txt"));
}
main();