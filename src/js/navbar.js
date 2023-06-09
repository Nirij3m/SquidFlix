function openFooterModal(){

    let modal = document.getElementById("mineModal");
    let btn = document.getElementById("myButton");

    btn.onclick = function() {
        modal.style.display = "block";
    }

    window.onclick = function(event) {
        if (event.target == modal) {
            modal.style.display = "none";
            document.getElementById("modalContainer").style.display = "none";
            document.getElementById("num").value = "";
        }
    }
}