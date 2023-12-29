
export default function setUpMenu(){
  let menuicn = document.querySelector(".menuicn"); 
  let closemenuicn = document.querySelector(".closemenuicn"); 
  let nav = document.querySelector(".navcontainer"); 
  
  
  
  let navOptions = document.querySelectorAll(".option1, .option2, .option3, .option4, .option5, .option6");
  
  navOptions.forEach(option => {
      option.addEventListener("click", function() {
        // Remove the "selected" class from all options
        navOptions.forEach(otherOption => {
          //
          // otherOption.style.backgroundColor = "#fafaff";
          otherOption.style.backgroundColor = "#d8d4d4";
          otherOption.style.color = "#3f3939";
          otherOption.style.borderLeft = "";
          // otherOption.classList.remove("selected");
        });

        option.style.backgroundColor = "#c3c1c5";
        option.style.color = "#e7e5e5";
        option.style.borderLeft  =  "5px solid #a2a2a2";
      });
    });
  
  
  menuicn.addEventListener("click", () => { 
      menuicn.style.display ='none';
      closemenuicn.style.display = 'block';
    nav.classList.toggle("navclose"); 
  })
  
  closemenuicn.addEventListener("click", () => { 
      menuicn.style.display ='block';
      closemenuicn.style.display = 'none';
    nav.classList.toggle("navclose"); 
  })
}


