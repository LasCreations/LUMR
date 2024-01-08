import User from "../modules/user.js";
import { createUserProfile } from './profile/view.js'


export function decoder() {
    if (window.location.href.includes('/secure/dashboard.html')) {
        var data = JSON.parse(atob(decodeURIComponent(window.location.search.replace('?data=', ''))));
        const user = new User(data.firstname, data.lastname, data.username, data.password, data.avatar, data.institutionName,
            data.rank, data.degrees, data.courses, data.yearStart, data.yearEnd);
            createSideNav();
            createUserProfile(user);
        
    }
}

function createSideNav(){
    let arrow = document.querySelectorAll(".arrow");
  for (var i = 0; i < arrow.length; i++) {
    arrow[i].addEventListener("click", (e)=>{
   let arrowParent = e.target.parentElement.parentElement;//selecting main parent of arrow
   arrowParent.classList.toggle("showMenu");
    });
  }
  let sidebar = document.querySelector(".sidebar");
  let sidebarBtn = document.querySelector(".bx-menu");
  console.log(sidebarBtn);
  sidebarBtn.addEventListener("click", ()=>{
    sidebar.classList.toggle("close");
  });
}