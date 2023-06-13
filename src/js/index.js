// ------- READ FILE -------
function readFileByName(fileName){

    //console.log(window.location.pathname); //Pour savoir ou mettre le ficher

    //console.log("poulpe");

    let xhr = new XMLHttpRequest();
    do {
        xhr.open("GET", fileName, false);
        xhr.send(null);
        //console.log("bloup");

    }while(xhr.status === 404); //si la page n'est pas trouver boucle

    // assumes status 200
    //console.log(xhr.responseText)
    //console.log("octopus");
    return xhr.responseText; //renvoie le contenu du fichier texte
}

function readFile(src1, src2){ //src1 et src2 en paramètre pour choisir les noms et ou ce trouve les fichiers
    readFileByName(src1);
    return readFileByName(src2);
}
// ------- READ FILE -------

function sugg(txt){

    let n = txt.length ; //taille du texte
    let count = 0 ; //pour savoir on est rendu où sur la ligne ( qu'elle point virgule )
    let counter = 0; //Le nombre de ligne

    let exe = ""; //temps d'execution
    let titre = ""; //titre du film
    let time = ""; //durée du film
    let genre = "" //le genre du film

    for ( let i = 0 ; i < n ; i ++ ){ // Boucle pour parcourir lettre par lettre

        if( counter == 0 || counter == 1){ //si ligne 1 et 2 alors ( lettre pour savoir ce que nous faisons et temps d'exécution)
            if ( txt[i] != "\n"){
                exe += txt[i] ;
                //console.log("exe : " + exe);
            }
            if ( txt[i] == "\n"){
                counter += 1 ; //une ligne en pluche
            }
        }
        else { //Début des lignes avec les films
            //count = 0 -> titre
            //count = 1 -> time
            //count = 2 -> genre
            if ( count == 0 && txt[i] != "\n" && txt[i] != ";"){
                titre += txt[i] ;   //concaténation du texte
                //console.log("titre : " + titre);
            }
            if ( count == 1 && txt[i] != "\n" && txt[i] != ";"){
                time += txt[i] ;  //concaténation du texte
                //console.log("time : " + time);
            }
            if ( count == 2 && txt[i] != "\n" && txt[i] != ";"){
                genre += txt[i] ; //concaténation du texte
                //console.log("genre : " + genre);
            }
            if ( txt[i] == ";" ){ //si ; alors on change de champ
                count = ( count + 1 ) % 3 ;
            }
            if ( txt[i] == "\n" || i == ( n - 1 ) ){ //rentour à la ligne ou fin du fichier on imprime car fin du film on passera au suivant après

                count = 0 ; //Pour recommencer
                
                if ( counter == 2 ){
                    document.getElementById("sug1").innerHTML = titre + " ( " + genre + " - " + time + " minutes )" ;
                    let randomImage1 = 'https://source.unsplash.com/random/?Octopus/' + Math.random(); //Obtention d'une image aléatoire
                    document.getElementById("img1").setAttribute("src", randomImage1); //changer le src de l'image pour l'avoir en random
                }
                if ( counter == 3 ){
                    document.getElementById("sug2").innerHTML = titre + " ( " + genre + " - " + time + " minutes )" ;
                    let randomImage2 = 'https://source.unsplash.com/random/?Octopus/' + Math.random(); //Obtention d'une image aléatoire
                    document.getElementById("img2").setAttribute("src", randomImage2); //changer le src de l'image pour l'avoir en random
                }
                if ( counter == 4 ){
                    document.getElementById("sug3").innerHTML = titre + " ( " + genre + " - " + time + " minutes )" ;
                    let randomImage3 = 'https://source.unsplash.com/random/?Octopus/' + Math.random(); //Obtention d'une image aléatoire
                    document.getElementById("img3").setAttribute("src", randomImage3); //changer le src de l'image pour l'avoir en random
                }
                if ( counter == 5 ){
                    document.getElementById("sug4").innerHTML = titre + " ( " + genre + " - " + time + " minutes )" ;
                    let randomImage4 = 'https://source.unsplash.com/random/?Octopus/' + Math.random(); //Obtention d'une image aléatoire
                    document.getElementById("img4").setAttribute("src", randomImage4); //changer le src de l'image pour l'avoir en random
                }

                counter += 1 ; //Pour savoir à qu'elle ligne on est rendu

                titre = ""; //réinitialisation
                time = ""; //réinitialisation
                genre = ""; //réinitialisation
            }
        }
    }
}

function main(){

    let random = readFile("/src/c/cmake-build-debug/ready1.txt", "/src/c/cmake-build-debug/res_random.txt"); //pour lire et lancer le fichier sugg
    //console.log(random);

    sugg(random); //affichage des suggestion pour les films

}

main();