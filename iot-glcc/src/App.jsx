import { useEffect, useState } from 'react';
import './App.css'
import { database } from './config';
import { ref, onValue, update } from "firebase/database"; 

function App() {
    const [enter, setEnter] = useState(0);
    const [exit, setExit] = useState(0);
    
    useEffect(() => {
        const enterRef = ref(database, "enter");
        const exitRef = ref(database, "exit");

        const unsubscribeEnter = onValue(enterRef, (snapshot) => {
            const val = snapshot.val();
            if (val !== null) setEnter(val);
        });
        const unsubscribeExit = onValue(exitRef, (snapshot) => {
            const val = snapshot.val();
            if (val !== null) setExit(val);
        });
        return () => {
            unsubscribeEnter();
            unsubscribeExit();
        };
    }, []);

    const handleReset = async () => {
        const updates = {
            enter: 0,
            exit: 0,
        };
        await update(ref(database), updates);
    }

    return (
        <div className="bg-gray-900 flex flex-col items-center justify-center h-screen">
            <div>
                <h1 className="text-6xl font-extrabold text-yellow-200 bg-clip-text mb-8">Total de personnes</h1>
            </div>
            <div className="flex flex-row items-center justify-center">
                <div className="text-center min-w-80">
                    <h1 className="hidden sm:inline text-3xl font-bold text-white">PIR Entrer: <span className="text-green-500">{enter}</span></h1>
                </div>
                <div className="min-w-96 text-center">
                    <h3 className="text-8xl inline-block font-extrabold text-transparent bg-clip-text bg-gradient-to-r from-pink-500 via-red-500 to-yellow-500">{enter-exit}</h3>
                </div>
                <div className="text-center min-w-80">
                    <h1 className="hidden sm:inline text-3xl font-bold text-white">PIR Sortie: <span className="text-red-500">{exit}</span></h1>
                </div>
            </div>
            <div>
<button className="text-white bg-gradient-to-r from-pink-500 via-red-500 to-yellow-500 font-semibold py-2 px-4 rounded-full mt-16 cursor-pointer hover:brightness-110 hover:text-white hover:drop-shadow-md" onClick={handleReset}>Réinitialiser
</button>
            </div>
        </div> 
    )
}

export default App
