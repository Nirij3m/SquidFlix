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

function link_nirina(){
    window.open("https://www.linkedin.com/in/nirina-macon-8b0692172/");
}

function link_lisa(){
    window.open("https://www.linkedin.com/in/lisa-crusson-69158122b/");
}

function link_amaury(){
    window.open("https://www.linkedin.com/in/amaury-77545725a/");
}

openFooterModal()