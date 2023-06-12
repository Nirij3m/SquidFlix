
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

function subscribe() {
    let connexionPanel = document.getElementById("container").cloneNode(true);
    connexionPanel.children[0].children[1].innerHTML = "Inscrivez-vous";

    document.getElementById("subscribe").addEventListener("click", function(){
        console.log("click");
        document.body.appendChild(connexionPanel);
    });
}
function main(){
    subscribe();
}