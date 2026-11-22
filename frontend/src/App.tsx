import { useEffect, useMemo, useRef, useState } from 'react'
import './App.css'

interface WordCounts {
  palindromes: number
  noRepeatedLetters: number
  noVowels: number
  noConsonants: number
  alternatingVowelsConsonants: number
  alphabeticalOrder: number
  reverseAlphabeticalOrder: number
  startEndSameLetter: number
  scrabbleScore20: number
  scrabbleScore30: number
  scrabbleScore40: number
  doubleConsecutiveLetters: number
  tripleConsecutiveLetters: number
  containsRarityWord: number
  isRarityWord: number
  countLengths: number[]
}

interface StatsData {
  totalWords: number
  counts: WordCounts
}

interface MatchedRule {
  label: string
  points: number
  rarity: string
}

const STARTING_CASH = 10000
const BET_PER_ROLL = 2000
const VOWELS = new Set(['a', 'e', 'i', 'o', 'u'])
const RARITY_WORDS = ['common', 'uncommon', 'rare', 'epic', 'legendary', 'mythical']

function isPalindrome(w: string) {
  return w.length > 0 && w === w.split('').reverse().join('')
}

function noRepeatedLetters(w: string) {
  return new Set(w.split('')).size === w.length
}

function containsNoVowels(w: string) {
  return ![...w].some((c) => VOWELS.has(c))
}

function containsNoConsonants(w: string) {
  return w.length > 0 && [...w].every((c) => VOWELS.has(c))
}

function alternatingVowelsConsonants(w: string) {
  if (w.length === 0) return false
  let prevIsVowel: boolean | null = null
  for (const c of w) {
    const currIsVowel = VOWELS.has(c)
    if (currIsVowel === prevIsVowel) return false
    prevIsVowel = currIsVowel
  }
  return true
}

function alphabeticalOrder(w: string) {
  for (let i = 1; i < w.length; i++) {
    if (w[i] < w[i - 1]) return false
  }
  return w.length > 0
}

function reverseAlphabeticalOrder(w: string) {
  for (let i = 1; i < w.length; i++) {
    if (w[i] > w[i - 1]) return false
  }
  return w.length > 0
}

function startEndSameLetter(w: string) {
  return w.length > 0 && w[0] === w[w.length - 1]
}

function consecutiveLetters(w: string) {
  if (!w.length) return 0
  let cur = 1
  let maxRun = 1
  for (let i = 1; i < w.length; i++) {
    if (w[i] === w[i - 1]) {
      cur++
      maxRun = Math.max(maxRun, cur)
    } else {
      cur = 1
    }
  }
  return maxRun
}

function scrabbleScore(w: string) {
  const scores: Record<string, number> = {
    a: 1, e: 1, i: 1, o: 1, u: 1, l: 1, n: 1, s: 1, t: 1, r: 1,
    d: 2, g: 2,
    b: 3, c: 3, m: 3, p: 3,
    f: 4, h: 4, v: 4, w: 4, y: 4,
    k: 5,
    j: 8, x: 8,
    q: 10, z: 10,
  }
  return [...w].reduce((sum, ch) => sum + (scores[ch] ?? 0), 0)
}

function getRarityLabel(odds: number) {
  if (odds > 0.1) return 'Common'
  if (odds > 0.02) return 'Uncommon'
  if (odds > 0.005) return 'Rare'
  if (odds > 0.001) return 'Epic'
  if (odds > 0.0001) return 'Legendary'
  return 'Mythical'
}

function getSuitBadge(rarity: string) {
  switch (rarity) {
    case 'Mythical':
      return { symbol: '♠', tone: 'suit-dark' }
    case 'Legendary':
      return { symbol: '♥', tone: 'suit-red' }
    case 'Epic':
      return { symbol: '♦', tone: 'suit-red' }
    case 'Rare':
      return { symbol: '♣', tone: 'suit-dark' }
    case 'Uncommon':
      return { symbol: '♦', tone: 'suit-red' }
    default:
      return { symbol: '♣', tone: 'suit-dark' }
  }
}

function evaluateWordPoints(targetWord: string, stats: StatsData | null) {
  const cleaned = targetWord.trim().toLowerCase()
  if (!cleaned || !stats || stats.totalWords === 0) {
    return { totalPoints: 0, rules: [] as MatchedRule[] }
  }

  const total = stats.totalWords
  const c = stats.counts
  const rules: MatchedRule[] = []

  const addRule = (label: string, freq: number) => {
    const safeFreq = Math.max(1, freq)
    const odds = safeFreq / total
    const points = Math.round(100 / odds)
    rules.push({
      label,
      points,
      rarity: getRarityLabel(odds),
    })
  }

  if (isPalindrome(cleaned)) addRule('Palindrome', c.palindromes)
  if (noRepeatedLetters(cleaned)) addRule('No Repeated Letters', c.noRepeatedLetters)
  if (containsNoVowels(cleaned)) addRule('Contains No Vowels', c.noVowels)
  if (containsNoConsonants(cleaned)) addRule('Contains No Consonants', c.noConsonants)
  if (alternatingVowelsConsonants(cleaned)) {
    addRule('Alternating Vowels and Consonants', c.alternatingVowelsConsonants)
  }
  if (alphabeticalOrder(cleaned)) addRule('Alphabetical Order', c.alphabeticalOrder)
  if (reverseAlphabeticalOrder(cleaned)) {
    addRule('Reverse Alphabetical Order', c.reverseAlphabeticalOrder)
  }
  if (startEndSameLetter(cleaned)) {
    addRule('Start and End with Same Letter', c.startEndSameLetter)
  }

  const scrabble = scrabbleScore(cleaned)
  if (scrabble >= 20) addRule('Scrabble Score >= 20', c.scrabbleScore20)
  if (scrabble >= 30) addRule('Scrabble Score >= 30', c.scrabbleScore30)
  if (scrabble >= 40) addRule('Scrabble Score >= 40', c.scrabbleScore40)

  const consec = consecutiveLetters(cleaned)
  if (consec >= 2) addRule('Double Consecutive Letters', c.doubleConsecutiveLetters)
  if (consec >= 3) addRule('Triple Consecutive Letters', c.tripleConsecutiveLetters)

  if (RARITY_WORDS.some((rw) => cleaned.includes(rw))) {
    addRule('Contains Rarity Word', c.containsRarityWord)
  }
  if (RARITY_WORDS.includes(cleaned)) {
    addRule('Is Rarity Word', c.isRarityWord)
  }

  const lenFreq =
    cleaned.length < c.countLengths.length ? c.countLengths[cleaned.length] : 0
  addRule(`Length of ${cleaned.length}`, lenFreq)

  const totalPoints = rules.reduce((acc, r) => acc + r.points, 0)
  return { totalPoints, rules }
}

function App() {
  const [word, setWord] = useState('')
  const [displayWord, setDisplayWord] = useState('')
  const [isSpinning, setIsSpinning] = useState(false)
  const [words, setWords] = useState<string[]>([])
  const [stats, setStats] = useState<StatsData | null>(null)
  const [dictInfo, setDictInfo] = useState<string>('')
  const [statusMsg, setStatusMsg] = useState<string>('Loading word dataset...')

  const [cash, setCash] = useState<number>(STARTING_CASH)
  const [lastPayout, setLastPayout] = useState<number | null>(null)
  const settledRollRef = useRef(false)

  useEffect(() => {
    const initializeData = async () => {
      try {
        const base = import.meta.env.BASE_URL
        const [statsRes, wordsRes] = await Promise.all([
          fetch(`${base}stats.json`),
          fetch(`${base}words.txt`),
        ])

        if (!statsRes.ok) {
          throw new Error('Could not load stats.json. Run the C++ backend first.')
        }
        if (!wordsRes.ok) {
          throw new Error('Could not load words.txt from frontend/public/words.txt.')
        }

        const statsJson: StatsData = await statsRes.json()
        const rawText = await wordsRes.text()
        const wordList = rawText
          .split(/\r?\n/)
          .map((w) => w.trim().toLowerCase())
          .filter(Boolean)

        setStats(statsJson)
        setWords(wordList)
        setStatusMsg(`Loaded ${statsJson.totalWords.toLocaleString()} words`)
      } catch (err) {
        setStatusMsg(err instanceof Error ? err.message : 'Failed to initialize data')
      }
    }

    initializeData()
  }, [])

  useEffect(() => {
    if (!isSpinning || words.length === 0) return

    settledRollRef.current = false
    let ticks = 0
    const totalTicks = 14
    const interval = window.setInterval(() => {
      ticks++
      const candidate = words[Math.floor(Math.random() * words.length)]
      setDisplayWord(candidate)

      if (ticks >= totalTicks && !settledRollRef.current) {
        settledRollRef.current = true
        window.clearInterval(interval)
        const finalWord = words[Math.floor(Math.random() * words.length)]
        const { totalPoints } = evaluateWordPoints(finalWord, stats)

        setDisplayWord(finalWord)
        setWord(finalWord)
        setLastPayout(totalPoints)
        setCash((prevCash) => prevCash + totalPoints)
        setIsSpinning(false)
      }
    }, 55)

    return () => window.clearInterval(interval)
  }, [isSpinning, words, stats])

  const selectRandomWord = () => {
    if (words.length === 0 || isSpinning || cash < BET_PER_ROLL) return
    setDictInfo('')
    setLastPayout(null)
    setCash((prev) => prev - BET_PER_ROLL)
    setIsSpinning(true)
  }

  const resetBankroll = () => {
    if (isSpinning) return
    setCash(STARTING_CASH)
    setLastPayout(null)
    setWord('')
    setDisplayWord('')
    setDictInfo('')
  }

  const getStats = async () => {
    const cleaned = word.trim().toLowerCase()
    if (!cleaned) return
    try {
      const response = await fetch(`https://freedictionaryapi.com/api/v1/entries/en/${cleaned}`)
      if (!response.ok) {
        setDictInfo('No dictionary entry found.')
        return
      }
      const info = await response.json()
      const firstDef =
        info?.entries?.[0]?.senses?.[0]?.definition ||
        info?.[0]?.meanings?.[0]?.definitions?.[0]?.definition ||
        'Entry found.'
      setDictInfo(firstDef)
    } catch {
      setDictInfo('Dictionary lookup unavailable.')
    }
  }

  const evaluation = useMemo(() => evaluateWordPoints(word, stats), [word, stats])
  const netRollResult = lastPayout !== null ? lastPayout - BET_PER_ROLL : null

  return (
    <main className="wonderland-shell">
      <header className="wonderland-banner">
        <span className="suit-red" aria-hidden="true">♥</span>
        <span>Wonderland Lexicon ({statusMsg})</span>
        <span className="suit-dark" aria-hidden="true">♠</span>
      </header>

      <section className="storybook-card">
        <div className="card-inner">
          <div className="bankroll-bar">
            <div className="bankroll-stat">
              <span className="bankroll-label">Cash:</span>
              <span className="bankroll-amount">${cash.toLocaleString()}</span>
            </div>
            <div className="bankroll-stat">
              <span className="bankroll-label">Bet / Roll:</span>
              <span className="bankroll-bet">${BET_PER_ROLL.toLocaleString()}</span>
            </div>
            {cash < BET_PER_ROLL && !isSpinning && (
              <button
                type="button"
                className="button-wonderland button-reset"
                onClick={resetBankroll}
              >
                Reset (${STARTING_CASH.toLocaleString()})
              </button>
            )}
          </div>

          {netRollResult !== null && !isSpinning && (
            <div className={`roll-outcome ${netRollResult >= 0 ? 'outcome-win' : 'outcome-loss'}`}>
              Roll Win/Loss:{' '}
              {netRollResult >= 0
                ? `+$${netRollResult.toLocaleString()}`
                : `-$${Math.abs(netRollResult).toLocaleString()}`}{' '}
              (Points Won: +${lastPayout?.toLocaleString()} vs -${BET_PER_ROLL.toLocaleString()} bet)
            </div>
          )}

          <div className="random-top-row">
            <span className="card-kicker">Down the Rabbit Hole</span>
            <button
              type="button"
              className="button-wonderland"
              onClick={selectRandomWord}
              disabled={words.length === 0 || isSpinning || cash < BET_PER_ROLL}
            >
              <span aria-hidden="true">🎩</span>
              {isSpinning
                ? 'Spinning...'
                : cash < BET_PER_ROLL
                  ? 'Not Enough Cash'
                  : `Get random word ($${BET_PER_ROLL.toLocaleString()})`}
            </button>
          </div>

          <div className={`slot-window ${isSpinning ? 'slot-spinning' : 'slot-landed'}`}>
            <span className="slot-suit" aria-hidden="true">♦</span>
            <div className="picked-word">{displayWord || word || '—'}</div>
            <span className="slot-suit" aria-hidden="true">♣</span>
          </div>
        </div>
      </section>

      <section className="storybook-card">
        <div className="card-inner">
          <div className="random-top-row">
            <div className="card-heading">Word Rarity &amp; Meaning</div>
            <button
              type="button"
              className="button-wonderland"
              onClick={getStats}
              disabled={!word.trim() || isSpinning}
            >
              Define
            </button>
          </div>

          <div className="results-container">
            <div className="summary-line">
              <span>{word.trim().length}-letter word</span>
              <span className="score-highlight">
                Total Score: +{evaluation.totalPoints.toLocaleString()} pts (${evaluation.totalPoints.toLocaleString()})
              </span>
            </div>

            {evaluation.rules.length > 0 && (
              <ul className="rules-list">
                {evaluation.rules.map((r) => {
                  const badge = getSuitBadge(r.rarity)
                  return (
                    <li key={r.label} className="rule-item">
                      <span>
                        • {r.label}: +{r.points.toLocaleString()} pts (${r.points.toLocaleString()}) ({r.rarity}
                      </span>
                      <span className={`card-chip ${badge.tone}`} aria-hidden="true">
                        {badge.symbol}
                      </span>
                      <span>)</span>
                    </li>
                  )
                })}
              </ul>
            )}

            {dictInfo && (
              <div className="definition-box">
                <strong>Definition:</strong> {dictInfo}
              </div>
            )}
          </div>
        </div>
      </section>
    </main>
  )
}

export default App