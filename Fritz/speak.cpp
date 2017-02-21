#include "speak.h"

#include <QProcess>
#include <QList>

 Speak::Speak()
{
    /* ' = pause */

    /* Vowel sounds */
    phono ah;              // ash
    ah.ipa = "æ";
    ah.lips = "aaah";
    phonos.append(ah);

    phono a;               // all
    a.ipa = "ɔː";
    a.lips = "oh";
    phonos.append(a);

    phono aa;              // father
    aa.ipa = "ɑː";
    a.lips = "aa";
    phonos.append(aa);

    phono e;               // better
    e.ipa = "ɛ";
    e.lips = "i";
    phonos.append(e);

    phono ay;              // day
    ay.ipa = "eɪ";
    ay.lips = "laa";
    phonos.append(ay);

    phono ea;              // earth
    ea.ipa = "ɜː";
    ea.lips = "sss";
    phonos.append(ea);

    phono i;               // drink
    i.ipa = "ɪ";
    i.lips = "i";
    phonos.append(i);

    phono ee;              // eat
    ee.ipa = "iː";
    ee.lips = "eee";
    phonos.append(ee);

    phono o;
    o.ipa = "ɒ";          // top
    o.lips = "oh";
    phonos.append(o);

    phono ou;
    ou.ipa = "ɔː";         // four
    ou.lips = "oooh";
    phonos.append(ou);

    phono oo;
    oo.ipa = "ʊ";         // foot
    oo.lips = "oh";
    phonos.append(oo);

    phono ooo;
    ooo.ipa = "uː";        // goose
    ooo.lips = "oooh";
    phonos.append(ooo);

    phono od;
    od.ipa = "ʌ";         // blood
    od.lips = "o//on_SpeakPhrase(value);h";
    phonos.append(od);

    phono on;
    on.ipa = "əʊ";         // bone
    on.lips = "fuh";
    phonos.append(on);

    phono ow;
    ow.ipa = "aʊ";        // cow
    ow.lips = "laa";
    phonos.append(ow);

    phono ai;
    ai.ipa = "eɪ";         // nail
    ai.lips = "fuh";
    phonos.append(ai);

    phono ii;
    ii.ipa = "aɪ";         // bite
    ii.lips = "i";
    phonos.append(ii);

    phono er;
    er.ipa = "iə";         // ear
    er.lips = "eee";
    phonos.append(er);

    phono b;
    b.ipa = "b";         // b
    b.lips = "mmm";
    phonos.append(b);

    phono p;
    p.ipa = "p";         // pee
    p.lips = "mmm";
    phonos.append(p);

    phono m;
    m.ipa = "m";         // mmm
    m.lips = "mmm";
    phonos.append(m);

    phono f;
    f.ipa = "f";         // fuh
    f.lips = "fuh";
    phonos.append(f);

    phono v;
    v.ipa = "v";         // vuh
    v.lips = "fuh";
    phonos.append(v);

}

 QString Speak::GetMouthShape(QString phon)
 {
     QVectorIterator<phono> i(phonos);
     while( i.hasNext())
     {
        phono p = i.next();
        if( phon.contains(p.ipa) )
            return p.lips;
     }
     return "sss";
 }

 QStringList Speak::TextToPhon(QString text)
 {
     QString command = "espeak -s120 -k20 -ven-uk-rp -q --ipa=3 ";
     command.append('"').append(text).append('"');

     QProcess process;
     process.start(command);
     process.waitForFinished();
     QString result(process.readAllStandardOutput());
     result.remove("\n");
     result.replace(" ","_ _");
     return result.split("_",QString::SkipEmptyParts);
 }


int Speak::TextToSpeech(QString text)
{
    QString command = "espeak -s120 -k20 -ven-uk-rp "; // was 130
    command.append('"').append(text).append('"');

    QProcess process;
    process.startDetached(command);
    return 0;
}

int Speak::TextToWave(QString text)
{
    QString command = "espeak -s130 -k20 -ven-uk-rp -w /tmp/out.wav ";
    command.append('"').append(text).append('"');

    QProcess process;
    process.start(command);
    process.waitForFinished();

    return 0;
}

int Speak::PlayWave()
{
    QString command = "aplay /tmp/out.wav";
    QProcess process;
    process.startDetached(command);
    return 0;
}
