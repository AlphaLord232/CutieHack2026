import { useEffect, useState } from 'react'
import './App.css'

function App() {

  const [word, setWord] = useState('');
  const [data, setData] = useState('');

  const handleValueChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setWord(e.target.value);
  }

  const initializeData = async () => {

    const response = await fetch('../backend/src/file.json');
    // setData(await response.json());
    console.log(await response.json());

    // const textResponse = await fetch('src/words.txt');
    // const newData = await textResponse.text().then(text => text.split('\n'));

    // setWords(newData);

    // const newLengths = new Array(50).fill(0);
    // for (let i = 0; i < newData.length; i++) {
    //   newLengths[newData[i].length]++;
    // }
    // setLengths(newLengths);
    // for (let i = 0; i < newLengths.length; i++) {
    //   console.log(`Length ${i}: ${newLengths[i]}`);
    // }
  }

  const getStats = async () => {
    const response = await fetch(`https://freedictionaryapi.com/api/v1/entries/en/${word}`);
    const info = await response.json();
    console.log(info);
  }

  useEffect(() => {
    initializeData();
  }, []);

  const getPoints = (frequency: number) => {
    return 0;
    // return ((words.length / frequency) * 100)
              // .toLocaleString('en-US', { maximumFractionDigits: 0 });
  }

  const selectRandomWord = () => {
    // const randomIndex = Math.floor(Math.random() * words.length);
    // setWord(words[randomIndex]);
    setWord("hi");
  }

  return (<>

    <div className='section-container'>
      <div className='random-word-label'>Random Word</div>
      <button className='button-primary' onClick={selectRandomWord}>Get random word</button>
      <div className='word-label'>{word}</div>
    </div>

    <div className='section-container'>
      <div className='input-container'>
        <div className='input-label'>Input a word...</div>
        <input className='word-input' value={word} onChange={handleValueChange}/>
        <button className='button-primary' onClick={getStats}>Go!</button>
      </div>
      <div className='results-container'>
        <div>{word.length}-letter word</div>
        <div>+20 pts</div>
      </div>
    </div>

  </>)
}

export default App
