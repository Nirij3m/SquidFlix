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

function recup(){

    //console.log("octopus");

    let counter = "000" ;
    //console.log(counter);

    let director = document.getElementById("searchDirector").value;
    let size = director.length ;
    //console.log("length : " + size);
    //console.log(director);

    if(director != ''){
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
        document.getElementById("searchDirector").value = director2 ;
    }

    let time = document.getElementById("searchTime").value;
    //console.log(time);

    if(time < 0){
        let time2 = time * ( -1 ) ;
        
        document.getElementById("searchTime").value = time2 ;
    }

    let genre = document.getElementById("searchGenre").value;
    //console.log(genre);

    if(director == '' && time == "" && genre == "None"){
        counter = "000";
    }
    else {
        if(director != '' && time != "" && genre != "None"){
            counter = "111";
        }
        else {
            if(director != '' && time == "" && genre == "None"){
                counter = "100";
            }
            else {
                if(director == '' && time != "" && genre == "None"){
                    counter = "010";
                }
                else {
                    if(director == '' && time == "" && genre != "None"){
                        counter = "001";
                    }
                    else {
                        if(director != '' && time != "" && genre == "None"){
                            counter = "110";
                        }
                        else {
                            if(director != '' && time == "" && genre != "None"){
                                counter = "101";
                            }
                            else {
                                if(director == '' && time != "" && genre != "None"){
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
    return counter ;
}

function clear(){

    card = document.getElementById("test1");
    document.getElementsByClassName("container1") = "";
    document.getElementsByClassName("container1") = card;

}

// ------- WRITE FILE -------
function writeFile(counter, id_form,func, destionnation) {

    //console.log("Poulpe");

    var element = document.createElement('a');
    let save = "";
    //console.log(save);
    //console.log("element : " + element);

    for(let j = 0; j < counter ; j ++){

        //console.log("id_form : " + id_form[j]);

        let text1 = document.getElementById(id_form[j]).value;
        //console.log("text : " + text1);

        let count = text1.length;
        //console.log("count : " + count);

        //console.log(func[j]);
        let textToSave = destionnation + ";" + func[j] + ";";
        //console.log(textToSave);

        for(let i = 0;i<=count-1;i++){
            textToSave += text1[i];
            //console.log("TextToSave_1 : " + textToSave);
            //console.log("text1[i] : " + text1[i]);
        }

        save += textToSave + "\n"
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

function find(){

    let counter = recup();

    clear();

    if ( counter == "000" ){
        console.log("Veuillez entrez quelque chose avant de rechercher\nPour voir l'intégralité de notre catalogue vous pouvez aller dans la catégorie Films.")
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

function results(txt){

    let n = txt.length ;
    let count = 0 ;
    let counter = 0;
    let suggestion = 1 ;

    let lettre = "";
    let exe = "";
    let director = "";
    let titre = "";
    let time = "";
    let genre = "";

    for ( let i = 0 ; i < n ; i ++ ){
        
        if ( counter === 1 || counter === 0 ){
            if ( counter === 1 && txt[i] != "\n"){
                exe += txt[i] ;
                //console.log("exe : " + exe);
            }
            if ( txt[i] == "\n"){
                counter += 1 ;
            }
            if ( counter === 0 && txt[i] != "\n"){
                lettre += txt[i];
            }
        }
        else {            
            if ( count == 0 && txt[i] != "\n" && txt[i] != ";"){
                director += txt[i] ;
                console.log("director : " + director);
            }
            if ( count == 1 && txt[i] != "\n" && txt[i] != ";"){
                titre += txt[i] ;
                console.log("titre : " + titre);
            }
            if ( count == 2 && txt[i] != "\n" && txt[i] != ";"){
                time += txt[i] ;
                console.log("time : " + time);
            }
            if ( count == 3 && txt[i] != "\n" && txt[i] != ";"){
                genre += txt[i] ;
                console.log("genre : " + genre);
            }
            if ( txt[i] == ";" ){
                count = ( count + 1 ) % 4 ;
            }
            if ( txt[i] == "\n" || i == ( n - 1 ) ){

                count = 0 ;

                if ( txt[0] == "R"){

                    if ( suggestion == 1 ){
                        document.getElementById("searchGenre2").value = genre ;
                        writeFile(1,['searchGenre2'],["findByGenre"], "S");
                        suggestion += 1 ;
                    }

                    let newCard = document.getElementsByClassName("card-box1")[0].cloneNode(true);
                    newCard.id ="";
                    console.log(newCard);

                    newCard.children[0].children[1].innerHTML = titre ;
                    newCard.children[0].children[2].innerHTML = genre ;
                    newCard.children[1].children[0].innerHTML = time ;
                    newCard.children[1].children[1].innerHTML = director ;

                    let randomImage = 'https://source.unsplash.com/random/?Octopus/' + Math.random(); //Obtention d'une image aléatoire

                    newCard.children[2].setAttribute("src", randomImage);

                    document.getElementsByClassName("container1")[0].appendChild(newCard);
                    console.log("bloup");
                }

                if ( txt[0] == "S"){

                    let newCard = document.getElementsByClassName("card-box2")[0].cloneNode(true);
                    newCard.id ="";
                    console.log(newCard);

                    newCard.children[0].children[1].innerHTML = titre ;
                    newCard.children[0].children[2].innerHTML = genre ;
                    newCard.children[1].children[0].innerHTML = time ;
                    newCard.children[1].children[1].innerHTML = director ;

                    let randomImage = 'https://source.unsplash.com/random/?Octopus/' + Math.random(); //Obtention d'une image aléatoire

                    newCard.children[2].setAttribute("src", randomImage);

                    document.getElementsByClassName("container2")[0].appendChild(newCard);
                    console.log("bloup");

                }

                titre = "" ;
                time = "" ;
                genre = "" ;
            }
        }
    }



}
// -------------------------

// -------------------------

function main(){

    //console.log("poulpe");

    find();

    //readFile();
    let myresults = readFile("/src/c/cmake-build-debug/ready.txt", "/src/c/cmake-build-debug/results.txt");
    console.log(myresults);

    results(myresults);
    setTimeout(() =>{}, "1000");

    let Sug = readFile("/src/c/cmake-build-debug/ready.txt", "/src/c/cmake-build-debug/results.txt");
    console.log(Sug);

    results(Sug);

}