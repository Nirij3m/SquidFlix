function animateCards(){
    Array.from(document.getElementsByClassName("card-box")).forEach((card) => {
       card.addEventListener("mouseover", () => { //Je over la card
            card.children[0].classList.add("fade-in-bg");
            card.children[1].classList.add("fade-in-bg");
            card.getElementsByClassName("title")[0].style.color = "#be743e";
            card.getElementsByClassName("genre")[0].style.color = "#4c4c4c";
           card.getElementsByClassName("duration")[0].style.color = "#4c4c4c";
           card.getElementsByClassName("genre")[0].style.color = "#595959";
           card.getElementsByClassName("director")[0].style.color = "#949494";
         });
       card.addEventListener("mouseout", () => { //Je quitte la card
            card.children[0].classList.remove("fade-in-bg");
            card.children[1].classList.remove("fade-in-bg");
           card.getElementsByClassName("title")[0].style.color = "#f1f1f1";
           card.getElementsByClassName("genre")[0].style.color = "#f1f1f1";
           card.getElementsByClassName("duration")[0].style.color = "#f1f1f1";
           card.getElementsByClassName("genre")[0].style.color = "#f1f1f1";
           card.getElementsByClassName("director")[0].style.color = "#f1f1f1";
       });
    });
}

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


function main(){
    animateCards();
    openFooterModal();
}
main();