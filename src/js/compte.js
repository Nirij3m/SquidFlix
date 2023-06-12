bool=true
function changer() {
    if(bool) {
        document.getElementById("pw").setAttribute("type","text")
        bool = false
    }
    else{
        document.getElementById("pw").setAttribute("type","password")
        bool = true
    }
}