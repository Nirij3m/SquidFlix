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
function writeFile(counter, id_form,func) {

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
        let textToSave = func[j] + ";";
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
            writeFile(1,['searchDirector'],["findByDirector"]);
        }
        else {
            if ( counter == "010" ){
                writeFile(1,['searchTime'],["findByTime"]);
            }
            else{
                if ( counter == "001" ){
                    writeFile(1,['searchGenre'],["findByGenre"]);
                }
                else{
                    if ( counter == "110" ){
                        writeFile(2,['searchDirector','searchTime'],["findByDirector","findByTime"]);
                    }
                    else{
                        if ( counter == "101" ){
                            writeFile(2,['searchDirector','searchGenre'],["findByDirector","findByGenre"]);
                        }
                        else{
                            if ( counter == "011" ){
                                writeFile(2,['searchTime','searchGenre'],["findByTime","findByGenre"]);
                            }
                            else{
                                if ( counter == "111" ){
                                    writeFile(3,['searchDirector','searchTime','searchGenre'],["findByDirector","findByTime","findByGenre"]);
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
    readFileByName("/src/js/ready.txt");
    return readFileByName("/src/js/results.txt");
}

function Results(txt){

    let n = txt.length ;
    let count = 0 ;
    let counter = 0;
    let movies ;
    let film ;

    let exe = "";
    let director = "";
    let time = "";
    let genre = "";

    for ( let i = 0 ; i < n ; i ++ ){

        if ( txt[i] == "\n" && counter == 0){
            counter += 1 ;
        }

        if ( counter == 0 ){
            exe += txt[i]
        }

        if ( txt[i] == ";"){
            count += 1 ;
            count = count%3 ;
        }

        if ( counter != 0 && count == 0 ){
            director += txt[i] ;
        }

        if ( counter != 0 && count == 1 ){
            time += txt[i] ;
        }

        if ( counter != 0 && count == 0 ){
            genre += txt[i] ;
        }

        if ( txt[i] == "\n" && counter != 0){

            film[0] = director;
            film[1] = time ;
            film[2] = genre ;

            movies[counter - 1] = film ;

            counter += 1 ;
        }

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