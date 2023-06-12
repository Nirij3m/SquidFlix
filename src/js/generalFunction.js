function animateCards(){
    Array.from(document.getElementsByClassName("card-box")).forEach((card) => {
       card.addEventListener("mouseover", () => { //Je over la card
            card.children[0].classList.add("fade-in-bg");
            card.children[1].classList.add("fade-in-bg");
            Array.from(document.getElementsByClassName("title")).forEach((title) => {
               title.style.color = "#e5941f";
            });
            Array.from(document.getElementsByClassName("genre")).forEach((genre) => {
                genre.style.color = "#797979";
            });
            Array.from(document.getElementsByClassName("duration")).forEach((duration) => {
                duration.style.color = "#797979";
            });
            Array.from(document.getElementsByClassName("director")).forEach((director) => {
                director.style.color = "#a9a9a9";
            });
         });
       card.addEventListener("mouseout", () => { //Je quitte la card
            card.children[0].classList.remove("fade-in-bg");
            card.children[1].classList.remove("fade-in-bg");
            Array.from(document.getElementsByClassName("title")).forEach((title) => {
                title.style.color = "#F2EDEB";
            });
            Array.from(document.getElementsByClassName("genre")).forEach((genre) => {
                genre.style.color = "#F2EDEB";
            });
            Array.from(document.getElementsByClassName("duration")).forEach((duration) => {
                duration.style.color = "#F2EDEB";
            });
            Array.from(document.getElementsByClassName("director")).forEach((director) => {
                director.style.color = "#F2EDEB";
            });
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