bool=true
function changer() {
    if(bool) {
        document.getElementById("pw").setAttribute("type","text") //rend visible le mot de passe
        bool = false
    }
    else{
        document.getElementById("pw").setAttribute("type","password") //rend invisible le mot de passe
        bool = true
    }
}