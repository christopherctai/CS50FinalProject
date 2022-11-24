
// const section1 = document.querySelector('section1')

// const faders = document.querySelectorAll('.animated')

// const appearOptions = {
//     threshold: 1
// };
// const appearOnScroll = new IntersectionObserver(function(
//     entries, 
//     appearOnScroll
//     ) {
//         entries.forEach(entry => {
//             if (!entry.isIntersecting) {
//                 return;
//             }
//             else {
//                 entry.target.classList.add('fadeInBottom');
//                 appearOnScroll.unobserve(entry.target);
//             }
//         })
//     }, 
//     appearOptions);

// faders.forEach(fader => {
//     appearOnScroll.observe(fader);
// })



// function showImages(el) {
//     var windowHeight = jQuery( window ).height();
//     $(el).each(function(){
//         var thisPos = $(this).offset().top;

//         var topOfWindow = $(window).scrollTop();
//         if (topOfWindow + windowHeight - 200 > thisPos ) {
//             $(this).addClass("fadeIn");
//         }
//     });
// }

// // if the image in the window of browser when the page is loaded, show that image
// $(document).ready(function() {
//         showImages('.star');
// });

// // if the image in the window of browser when scrolling the page, show that image
// $(window).scroll(function() {
//         showImages('.star');
// });




// $(document).on("scroll", function() {
//     var pageTop = $(document).scrollTop();
//     var pageBottom = pageTop + $(window).height();
//     var tags = $(".tag");

//     for (var i = 0; i < tags.length; i++) {
//         var tag = tags[i];
//         if($(tag).position().top < pageBottom) {
//             $(tag).addClass("visible");
//         }
//         else {
//             $(tag).removeClass("visible");
//         }
//     }
// }); 


