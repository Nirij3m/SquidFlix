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

function main(){

    let random = readFile("/src/c/cmake-build-debug/ready1.txt", "/src/c/cmake-build-debug/res_director.txt");
    console.log(random);

}