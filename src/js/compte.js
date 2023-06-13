
let bool = true;
function changer() {

    if (bool) {
        document.getElementById("pw").setAttribute("type", "text") //rend visible le mot de passe
        bool = false;
    } else {
        document.getElementById("pw").setAttribute("type", "password") //rend invisible le mot de passe
        bool = true;
    }
}

function hash(str){
    let encodedMessage = btoa(str);
    return encodedMessage;
}

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

function propo_movie(){
    console.log("Bob");
    document.getElementsByClassName("container")[0].innerHTML = "";
}

function connect(){

    let bd = [['user','pass'],['poulpe', 'octopus']]

    document.getElementsByTagName("input")[2].addEventListener("click", function(){
        let user = document.getElementsByClassName("input")[0].value;
        let pass = document.getElementsByClassName("input")[1].value;
        if(user === "" || pass === ""){
            alert("Veuillez remplir tous les champs");
        }
        else{
            let here = 0 ;
            let size = bd.length ;
            for ( let i = 0 ; i < size ; i ++ ){
                //console.log(bd[i][0]);
                //console.log(bd[i][1]);
                if ( user === bd[i][0] && pass === bd[i][1]){
                    alert("Vous êtes connecté");
                    propo_movie();
                    here = 1 ;
                }
            }
            if ( here == 0 ){
                alert("Utilisateur ou Mot de Passe incorrect");
            }

            /*if(user === "user" && pass === "pass"){
                alert("Vous êtes connecté");
                propo_movie();
                //document.location.href="index.html";
            }
            if(user === "poulpe" && pass === "octopus"){
                alert("Vous êtes connecté en mode admin");
                propo_movie();
                //document.location.href="index.html";
            }
            else{
                alert("Utilisateur ou Mot de Passe incorrect");
            }*/
        }
    });
}

function subscribe() {
    let connexionPanel = document.getElementsByClassName("container")[0].cloneNode(true);
    connexionPanel.children[0].children[0].innerHTML = "Inscrivez-vous";
    connexionPanel.children[6].remove();
    connexionPanel.id = "subPanel";
    connexionPanel.children[3].children[1].id = "subPass";
    console.log(connexionPanel.children[3].children[1]);
    console.log(connexionPanel.children[1].children[1]);
    connexionPanel.children[1].children[1].id = "subUser";

    connexionPanel.getElementsByClassName("envoyer")[0].addEventListener("click", function(){
        let username = connexionPanel.getElementsByTagName("input")[0].value;
        let password = connexionPanel.getElementsByTagName("input")[1].value;

        let finalPass = username + " " + password;
        console.log(finalPass);
        document.getElementById("finalPass").value = finalPass;
        writeFile(1, ['finalPass'], ["createUser"], "Z");
    });

    document.getElementById("subscribe").addEventListener("click", function(){
        document.body.appendChild(connexionPanel);
    });
}
function main(){
    subscribe();
    connect();
}
main()