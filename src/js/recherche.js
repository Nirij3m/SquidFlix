function recup(){

    //console.log("octopus");

    let counter = "000" ;

    let director = document.getElementById("searchDirector").value;
    //console.log("length : " + director.length);
    //console.log(director);

    if(director != ''){
        counter[0] += 1 ;
    }

    let time = document.getElementById("searchTime").value;
    //console.log(time);

    if(time != ''){
        counter[1] += 1 ;
    }

    let genre = document.getElementById("searchGenre").value;
    //console.log(genre);

    if(genre != 'None'){
        counter[2] += 1 ;
    }

    return counter ;
}

// ------- WRITE FILE -------
// ------- WRITE FILE -------
function writeFile(counter, id_form,func) {

    //console.log("Poulpe");

    var element = document.createElement('a');

    //console.log("element : " + element);
    //console.log("id_form : " + id_form);

    let text1 = document.getElementById(id_form).value;
    //console.log("text : " + text1);

    let count = text1.length;
    //console.log("count : " + count);

    let textToSave = counter + "\n" + func + ";";

    for(let i = 0;i<=count-1;i++){
        textToSave += text1[i];
        //console.log("TextToSave_1 : " + textToSave);
        //console.log("text1[i] : " + text1[i]);
    }

    //console.log(textToSave);

    element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(textToSave));
    element.setAttribute('download', 'request.txt');

    element.style.display = 'none';
    document.body.appendChild(element);
    element.click();
    document.body.removeChild(element);

   // text1.submit();
}
// -------------------------

function findDirector(){

    //let director = document.getElementById("searchDirector").value;
    //console.log("director : " + director);
    writeFile('searchDirector',"findByDirector");

}

function main(){

    console.log("poulpe");
    recup();

    if ( recup() == 0 ){
        console.log("Veuillez entrez quelque chose avant de rechercher\nPour voir l'intégralité de notre tacalogue vous pouvez aller dans la catégorie Films.")
    }
    if ( recup() == 1 ){
        
    }
    if ( recup() == 2 ){
        
    }
    if ( recup() == 3 ){
        
    }

}

main();