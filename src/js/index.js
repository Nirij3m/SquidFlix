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
// ------- READ FILE -------

function sugg(txt){

    let n = txt.length ;
    let count = 0 ;
    let counter = 0;

    let exe = "";
    let titre = "";
    let time = "";
    let genre = ""

    for ( let i = 0 ; i < n ; i ++ ){

        if( counter == 0 || counter == 1){
            if ( txt[i] != "\n"){
                exe += txt[i] ;
                console.log("exe : " + exe);
            }
            if ( txt[i] == "\n"){
                counter += 1 ;
            }
        }
        else {
            if ( count == 0 && txt[i] != "\n" && txt[i] != ";"){
                titre += txt[i] ;
                console.log("titre : " + titre);
            }
            if ( count == 1 && txt[i] != "\n" && txt[i] != ";"){
                time += txt[i] ;
                console.log("time : " + time);
            }
            if ( count == 2 && txt[i] != "\n" && txt[i] != ";"){
                genre += txt[i] ;
                console.log("genre : " + genre);
            }
            if ( txt[i] == ";" ){
                count = ( count + 1 ) % 3 ;
            }
            if ( txt[i] == "\n" || i == ( n - 1 ) ){

                count = 0 ;
                
                if ( counter == 2 ){
                    document.getElementById("sug1").innerHTML = titre + "( " + genre + " - " + time + " minutes )" ;
                    let randomImage1 = 'https://source.unsplash.com/random/?Octopus/' + Math.random(); //Obtention d'une image aléatoire
                    document.getElementById("img1").setAttribute("src", randomImage1);
                }
                if ( counter == 3 ){
                    document.getElementById("sug2").innerHTML = titre + "( " + genre + " - " + time + " minutes )" ;
                    let randomImage2 = 'https://source.unsplash.com/random/?Octopus/' + Math.random(); //Obtention d'une image aléatoire
                    document.getElementById("img2").setAttribute("src", randomImage2);
                }
                if ( counter == 4 ){
                    document.getElementById("sug3").innerHTML = titre + "( " + genre + " - " + time + " minutes )" ;
                    let randomImage3 = 'https://source.unsplash.com/random/?Octopus/' + Math.random(); //Obtention d'une image aléatoire
                    document.getElementById("img3").setAttribute("src", randomImage3);
                }
                if ( counter == 5 ){
                    document.getElementById("sug4").innerHTML = titre + "( " + genre + " - " + time + " minutes )" ;
                    let randomImage4 = 'https://source.unsplash.com/random/?Octopus/' + Math.random(); //Obtention d'une image aléatoire
                    document.getElementById("img4").setAttribute("src", randomImage4);
                }

                counter += 1 ;

                titre = "";
                time = "";
                genre = "";
            }
        }
    }
}

function main(){

    let random = readFile("/src/js/ready1.txt", "/src/js/res_random.txt");
    console.log(random);

    sugg(random);

}

main();