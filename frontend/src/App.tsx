import { useEffect, useState } from 'react'
import './App.css'

function App() {

  const [word, setWord] = useState('');
  const [numWords, setNumWords] = useState(0);
  const [lengths, setLengths] = useState(new Array(50).fill(0));

  const handleValueChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setWord(e.target.value);
  }

  const initializeData = async () => {
    const textResponse = await fetch('src/words.txt');
    const newData = await textResponse.text().then(text => text.split('\n'));

    setNumWords(newData.length);

    const newLengths = new Array(50).fill(0);
    for (let i = 0; i < newData.length; i++) {
      newLengths[newData[i].length]++;
    }
    setLengths(newLengths);
    for (let i = 0; i < newLengths.length; i++) {
      console.log(`Length ${i}: ${newLengths[i]}`);
    }
  }

  const getStats = async () => {
    const response = await fetch(`https://freedictionaryapi.com/api/v1/entries/en/${word}`);
    const data = await response.json();
    console.log(data);
  }

  useEffect(() => {
    initializeData();
  }, []);

  const getPoints = (frequency: number) => {
    return ((numWords / frequency) * 100).toLocaleString('en-US', { maximumFractionDigits: 0 });
  }

  return (<>
    <div className='input-container'>
      <div className='input-label'>Input a word... </div>
      <input className='word-input' value={word} onChange={handleValueChange}/>
      <button className='button-primary' onClick={getStats}>Go!</button>
    </div>
    <div className='results-container'>
      <div>{word.length}-letter word</div>
      <div>+{getPoints(lengths[word.length])} pts</div>
    </div>
  </>)

  // const [count, setCount] = useState(0)

  // return (
  //   <>
  //     <section id="center">
  //       <div className="hero">
  //         <img src={heroImg} className="base" width="170" height="179" alt="" />
  //         <img src={reactLogo} className="framework" alt="React logo" />
  //         <img src={viteLogo} className="vite" alt="Vite logo" />
  //       </div>
  //       <div>
  //         <h1>Get started</h1>
  //         <p>
  //           Edit <code>src/App.tsx</code> and save to test <code>HMR</code>
  //         </p>
  //       </div>
  //       <button
  //         type="button"
  //         className="counter"
  //         onClick={() => setCount((count) => count + 1)}
  //       >
  //         Count is {count}
  //       </button>
  //     </section>

  //     <div className="ticks"></div>

  //     <section id="next-steps">
  //       <div id="docs">
  //         <svg className="icon" role="presentation" aria-hidden="true">
  //           <use href="/icons.svg#documentation-icon"></use>
  //         </svg>
  //         <h2>Documentation</h2>
  //         <p>Your questions, answered</p>
  //         <ul>
  //           <li>
  //             <a href="https://vite.dev/" target="_blank">
  //               <img className="logo" src={viteLogo} alt="" />
  //               Explore Vite
  //             </a>
  //           </li>
  //           <li>
  //             <a href="https://react.dev/" target="_blank">
  //               <img className="button-icon" src={reactLogo} alt="" />
  //               Learn more
  //             </a>
  //           </li>
  //         </ul>
  //       </div>
  //       <div id="social">
  //         <svg className="icon" role="presentation" aria-hidden="true">
  //           <use href="/icons.svg#social-icon"></use>
  //         </svg>
  //         <h2>Connect with us</h2>
  //         <p>Join the Vite community</p>
  //         <ul>
  //           <li>
  //             <a href="https://github.com/vitejs/vite" target="_blank">
  //               <svg
  //                 className="button-icon"
  //                 role="presentation"
  //                 aria-hidden="true"
  //               >
  //                 <use href="/icons.svg#github-icon"></use>
  //               </svg>
  //               GitHub
  //             </a>
  //           </li>
  //           <li>
  //             <a href="https://chat.vite.dev/" target="_blank">
  //               <svg
  //                 className="button-icon"
  //                 role="presentation"
  //                 aria-hidden="true"
  //               >
  //                 <use href="/icons.svg#discord-icon"></use>
  //               </svg>
  //               Discord
  //             </a>
  //           </li>
  //           <li>
  //             <a href="https://x.com/vite_js" target="_blank">
  //               <svg
  //                 className="button-icon"
  //                 role="presentation"
  //                 aria-hidden="true"
  //               >
  //                 <use href="/icons.svg#x-icon"></use>
  //               </svg>
  //               X.com
  //             </a>
  //           </li>
  //           <li>
  //             <a href="https://bsky.app/profile/vite.dev" target="_blank">
  //               <svg
  //                 className="button-icon"
  //                 role="presentation"
  //                 aria-hidden="true"
  //               >
  //                 <use href="/icons.svg#bluesky-icon"></use>
  //               </svg>
  //               Bluesky
  //             </a>
  //           </li>
  //         </ul>
  //       </div>
  //     </section>

  //     <div className="ticks"></div>
  //     <section id="spacer"></section>
  //   </>
  // )
}

export default App
