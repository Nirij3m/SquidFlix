function recup(){

    console.log("octopus");

    let director = document.getElementById("searchDirector").value;
    console.log("length : " + director.length);
    console.log(director);

    let time = document.getElementById("searchTime").value;
    console.log(time);

    let genre = document.getElementById("searchGenre").value;
    console.log(genre);

}

// ------- WRITE FILE -------
// ------- WRITE FILE -------
function writeFile(id_form,func) {

    var element = document.createElement('a');

    let text1 = document.getElementById(id_form);
    let count = text1.elements.length;
    let textToSave = func;
    for(let i = 0;i<count-1;i++){
        textToSave += ";" + text1[i].value;
    }

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

    let director = document.getElementById("searchDirector").value;
    console.log("director : " + director);
    writeFile(searchDirector,"findByDirector");

}

function main(){

    console.log("poulpe");
    recup();

}

main();