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

    if ( counter == "000" ){
        console.log("Veuillez entrez quelque chose avant de rechercher\nPour voir l'intégralité de notre tacalogue vous pouvez aller dans la catégorie Films.")
    }
    else{
        if ( counter == "100" ){
            writeFile(1,['searchDirector'],["findByDirector"], "R");
        }
        else {
            if ( counter == "010" ){
                writeFile(1,['searchTime'],["findByTime"], "R");
            }
            else{
                if ( counter == "001" ){
                    writeFile(1,['searchGenre'],["findByGenre"], "R");
                }
                else{
                    if ( counter == "110" ){
                        writeFile(2,['searchDirector','searchTime'],["findByDirector","findByTime"], "R");
                    }
                    else{
                        if ( counter == "101" ){
                            writeFile(2,['searchDirector','searchGenre'],["findByDirector","findByGenre"], "R");
                        }
                        else{
                            if ( counter == "011" ){
                                writeFile(2,['searchTime','searchGenre'],["findByTime","findByGenre"], "R");
                            }
                            else{
                                if ( counter == "111" ){
                                    writeFile(3,['searchDirector','searchTime','searchGenre'],["findByDirector","findByTime","findByGenre"], "R");
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

function readFile(){
    readFileByName("/src/c/ready.txt");
    return readFileByName("/src/c/cmake-build-debug/results.txt");
}

function Results(txt){

    let n = txt.length ;
    let count = 0 ;
    let counter = -1;
    let suggestion = 1 ;

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

            if( txt[0] == "R" && i > 1 ){
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

                        if ( suggestion == 1 ){
                            document.getElementById("searchGenre2").value = genre ;
                            writeFile(1,['searchGenre'],["findByGenre"], "S");
                            suggestion += 1 ;
                        }

                        let newCard = document.getElementsByClassName("container1")[1].cloneNode(true);
                        console.log(newCard);
                        newCard.children[0].children[0].children[1].innerHTML = titre ;
                        newCard.children[0].children[0].children[2].innerHTML = genre ;
                        newCard.children[0].children[1].children[0].innerHTML = time ;

                        let randomImage = 'https://source.unsplash.com/random/?Octopus/' + Math.random(); //Obtention d'une image aléatoire

                        newCard.children[0].children[2].setAttribute("src", randomImage);

                        document.getElementsByClassName("container")[0].appendChild(newCard);

                        titre = "";
                        time = "";
                        genre = "";
                    }

                }
            }
            else {

                if( txt[0] == "S" && i > 1 ){
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
    
                            let newCard = document.getElementsByClassName("container2")[1].cloneNode(true);
                            console.log(newCard);
                            newCard.children[0].children[0].children[1].innerHTML = titre ;
                            newCard.children[0].children[0].children[2].innerHTML = genre ;
                            newCard.children[0].children[1].children[0].innerHTML = time ;
    
                            let randomImage = 'https://source.unsplash.com/random/?Octopus/' + Math.random(); //Obtention d'une image aléatoire
    
                            newCard.children[0].children[2].setAttribute("src", randomImage);
    
                            document.getElementsByClassName("container")[0].appendChild(newCard);
    
                            titre = "";
                            time = "";
                            genre = "";
                        }
                    }

                }

            }
        }

        //console.log(exe);
        //console.log(titre);
        //console.log(time);
        //console.log(genre);
        //console.log(movies);
        //console.log(film);

    }
}
// -------------------------

// -------------------------

function main(){

    console.log("poulpe");

    find();

    //readFile();
    let myResults = readFile();
    console.log(myResults);

    Results(myResults);

}