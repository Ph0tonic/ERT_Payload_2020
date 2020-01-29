
# Procedure

IMU -> 9 axe

## Infos

- mercredi soir assemblage fusée
- mercredi soir Spagethi test -> certifée
- jeudi matin -> armement (Arduino uniquement)

## Signaux sonore

- 1 bit -> State / Système par système

## Signaux Physique

- Armed -> got on ready state -> Signal sonore !

## Signaux RF

- getState -> Return current state of the arduino
- shutdown (ready to standby) -> go to standBy mode -> Raspberry pi go to sleep
- wake (standby to idle) -> Wake up the pi
- inject (standby to injected) -> launch inject and send back image
- confirmInject -> Confirmation de l'injection
- by-pass inject -> If abort has been done
- rec (Start recording)
- abort -> Goto standby

## Triggers

- decollage -> 3G pendant 500 ms
- landed -> 10 minutes après décollage fin enregistrement

## State

- off -> éteint
- idle -> Arduino et PI démarré
- standby -> Arduino make pi in (sleep mode/steady state)
- injected -> Levures injectés, en attente 
- ready -> both online and levure injectés
- recording -> Start detecting decollage
- landed -> When landed triggered -> emit GPS / (son)

## To be defined

- Injection ...
